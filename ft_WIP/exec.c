/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:28:34 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/17 22:52:31 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_dup : duplique les descripteurs de fichiers pour le processus enfant
** @data : structure contenant les données du programme
** @i : numéro du processus enfant
**
** Cette fonction utilise l'appel système dup2 pour dupliquer les descripteurs
** de fichiers appropriés pour chaque processus enfant.
** - Si i est égal à 0, cela signifie que c'est le premier processus enfant
** - Si i est égal à data->n_child - 1, signifie que c'est le dernier enfant
** - Dans tous les autres cas, c'est un processus enfant intermédiaire
** Pour chaque cas, on duplique le descripteur de fichier approprié pour
** l'entrée et la sortie standard.
*/

void ft_dup(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd[0] == -1)
			dispatch_exit(cmd, 555);
		else if (cmd->fd[1] == -1)
			dispatch_exit(cmd, 666);
		dup2(cmd->fd[0], STDIN_FILENO);
		dup2(cmd->fd[1], STDOUT_FILENO);
		cmd = cmd->next;
	}
}

/*
** Open files : ouvre les fichiers de redirection pour le processus parent
** @data : structure contenant les données du programme
**
** Cette fonction ouvre les fichiers de redirection pour le processus parent.
** On ouvre ensuite le fichier de redirection d'entrée et de sortie.
** Enfin, on ouvre les pipes pour les processus enfants.
*/

int open_files(t_cmd *cmd)
{
	t_cmd *tmp;
	t_redir *redir;

	tmp = cmd;
	redir = tmp->redir;
	while (cmd && redir)
	{
		if (redir->type == REDIR_IN)
			cmd->fd[0] = open(redir->file, O_RDONLY, 0644);
		else if (redir->type == REDIR_OUT)
			cmd->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			cmd->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		cmd = cmd->next;
	}
	return (0);
}

void open_pipes(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	if (!tmp->next)
		return;
	tmp = tmp->next;
	while (tmp)
	{
		pipe(tmp->fd);
		tmp = tmp->next;
	}
	tmp = cmd;
	while (tmp)
	{
		tmp->fd[0] = tmp->fd[1];
		tmp->fd[1] = tmp->next->fd[1];
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
*/

void child(t_cmd *cmd)
{

	ft_dup(cmd);
	if (cmd->fd[0] != -1)
		close(cmd->fd[0]);
	if (cmd->fd[1] != -1)
		close(cmd->fd[1]);
	close_pipes(cmd, -1);
	printf("cmd->envp=%s\n", cmd->envp[0]);
	if (cmd->name)
		cmd->name = get_path(cmd->name, cmd->envp);
	printf("cmd->name = %s, cmd->argv[0] = %s\n", cmd->name, cmd->argv[0]);
	if (cmd->name)
		execve(cmd->name, cmd->argv, cmd->envp);
	ft_msg("Command not found", cmd->name);
	if (cmd->argv)
		ft_free_tab_str(cmd->argv, -1);
	dispatch_exit(cmd, 127);
}

void init_fd(t_cmd *cmd)
{
	open_pipes(cmd);
	open_files(cmd);
}

int ft_exec(t_cmd *cmd)
{
	t_cmd *tmp;

	if (!cmd)
		return (1);
	tmp = cmd;
	init_fd(tmp);
	// 	while (tmp && tmp->pid[i]) utilisez avec pid[i] = FULL;
	while (tmp)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			dispatch_exit(tmp, 8);
		printf("t------mp->envp: %s\n", tmp->envp[0]);
		if (!tmp->pid)
			child(tmp);
		tmp = tmp->next;
	}
	dispatch_exit(tmp, 777);
	return (0);
}
