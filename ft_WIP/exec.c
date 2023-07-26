/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:28:34 by mabimich          #+#    #+#             */
/*   Updated: 2023/07/26 17:48:37 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Open files : ouvre les fichiers de redirection pour le processus parent
** @data : structure contenant les données du programme
**
** Cette fonction ouvre les fichiers de redirection pour le processus parent.
** On ouvre ensuite le fichier de redirection d'entrée et de sortie.
** Enfin, on ouvre les pipes pour les processus enfants.
*/

int	open_files(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = cmd;
	redir = tmp->redir;
	while (cmd && redir)
	{
		if (redir->type == REDIR_IN)
			cmd->fd[0] = open(redir->file, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			cmd->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			cmd->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		redir = redir->next;
	}
	if (cmd->fd[0] == -1)
		dispatch_exit(cmd, 555);
	else if (cmd->fd[1] == -1)
		dispatch_exit(cmd, 666);
	return (0);
}

void	open_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	tmp->fd[0] = STDIN_FILENO;
	tmp->fd[1] = STDOUT_FILENO;
	if (!tmp->next)
		return ;
	tmp = tmp->next;
	while (tmp)
	{
		pipe(tmp->fd);
		tmp = tmp->next;
	}
	tmp = cmd;
	while (tmp->next)
	{
		tmp->fd[1] = tmp->next->fd[1];
		tmp = tmp->next;
	}
	tmp->fd[1] = STDOUT_FILENO;
}

int	ft_envlist_to_array(t_cmd *cmd);

void	close_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd->head;
	if (!tmp->next)
		return ;
	while (tmp)
	{
		if (tmp->fd[0] != STDIN_FILENO)
			close(tmp->fd[0]);
		if (tmp->fd[1] != STDOUT_FILENO)
			close (tmp->fd[1]);
		tmp = tmp->next;
	}
}

/*
** Child : fonction exécutée par chaque processus enfant
** @cmd : structure contenant les données du programme
**
** Cette fonction est exécutée par chaque processus enfant.
** On duplique les descripteurs de fichiers pour le processus enfant avec ft_dup.
** On ferme ensuite les descripteurs de fichiers et les pipes inutiles.
** On sépare la commande en arguments avec ft_split.
** On exécute la commande avec execve.
** Si la commande n'est pas trouvée, elle affiche un message d'erreur.
** Enfin, elle appelle la fonction dispatch_exit pour quitter le programme.
** Le code de sortie est 127 si la commande n'est pas trouvée.
** Le code de sortie est 126 si la commande n'est pas exécutable.
** Le code de sortie est 126 si la commande est un répertoire.
** Le code de sortie est 21 si la commande est vide.
*/

void	child(t_cmd *cmd)
{
	char		*path;
	struct stat	st;

	ft_envlist_to_array(cmd);
	open_files(cmd);
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close_pipes(cmd);
	if (!cmd->name)
		dispatch_exit(cmd, 21);
	path = get_path(cmd->name, cmd->envp);
	if (path && stat(path, &st) != -1 && (access(path, F_OK | X_OK)
			|| S_ISDIR(st.st_mode)))
	{
		if (S_ISDIR(st.st_mode))
			ft_msg(cmd->name, "is a directory");
		else
			ft_msg(cmd->name, "command found but not executable");
		dispatch_exit(cmd, 126);
	}
	if (path && cmd->argv && cmd->argv[0])
		execve(path, cmd->argv, cmd->envp);
	ft_msg(cmd->name, "command not found");
	// if (cmd->argv)
	// 	ft_free_tab_str(cmd->argv, -1);
	dispatch_exit(cmd, 127);
}

int	ft_exec(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		out;

	if (!cmd)
		return (1);
	tmp = cmd;
	open_pipes(tmp);
	while (tmp && tmp->pid)
	{
		// write(2, "______-------------------______\n", 33);
		out = ft_bltin_tester(&tmp);
		if (out == 0)
			out = ft_fun_builder(&tmp);
		if (out == 0)
			tmp->pid = fork();
		if (out == 2 && !tmp->head->next)
			dispatch_exit(tmp, 9);
		if (tmp->pid == -1)
			dispatch_exit(tmp, 8);
		if (!tmp->pid)
			child(tmp);
		tmp = tmp->next;
	}
	dispatch_exit(cmd->head, 777);
	return (0);
}
