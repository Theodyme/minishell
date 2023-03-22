/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:28:34 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/22 18:42:23 by mabimich         ###   ########.fr       */
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

void ft_check_fd(t_cmd *cmd)
{
	t_cmd *tmp;
	t_cmd *head;

	tmp = cmd;
	head = cmd->head;
	while (head)
	{
		printf("head->name=%s, head->fd[0]=%d, head->fd[1]=%d\n", head->name, head->fd[0], head->fd[1]);
		head = head->next;
	}
	printf("\n");
}

void ft_dup(t_cmd *cmd)
{
	//ft_check_fd(cmd);
	if (cmd->fd[0] == -1)
		dispatch_exit(cmd, 555);
	else if (cmd->fd[1] == -1)
		dispatch_exit(cmd, 666);
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);

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
	// printf fd[0] et fd[1] avant ouverture
	while (cmd && redir)
	{
		if (redir->type == REDIR_IN)
			cmd->fd[0] = open(redir->file, O_RDONLY, 0644);
		else if (redir->type == REDIR_OUT)
			cmd->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			cmd->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		redir = redir->next;
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
	while (tmp->next)
	{
		tmp->fd[1] = tmp->next->fd[1];
		tmp = tmp->next;
	}
	tmp->fd[1] = STDOUT_FILENO;
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

int ft_envlist_to_array(t_cmd *cmd);

void close_pipes2(t_cmd *cmd, int i)
{
	t_cmd *tmp;

	tmp = cmd->head;
	if (!tmp->next)
		return ;
	while (tmp)
	{
		fprintf(stderr, "%d: close_pipes2: tmp->name=%s, tmp->fd[0]=%d, tmp->fd[1]=%d____\n", getpid(), tmp->name, tmp->fd[0], tmp->fd[1]);
		if (tmp->fd[0] != STDIN_FILENO)
		{
			fprintf(stderr, "%d: close_pipes2: close(tmp->fd[0]:%d)\n", getpid(), tmp->fd[0]);
			close(tmp->fd[0]);
		}
		if (tmp->fd[1] != STDOUT_FILENO)
		{
			fprintf(stderr, "%d: close_pipes2: close(tmp->fd[1]:%d)\n", getpid(), tmp->fd[1]);
			close (tmp->fd[1]);
		}
		i++;
		tmp = tmp->next;
	}
	// fprintf(stderr, "end closing pipe\n");
}

void child(t_cmd *cmd)
{
	ft_envlist_to_array(cmd);
	// fprintf(stderr, "____OPEN FILES from %d\n", getpid());
	open_files(cmd);
	// fprintf(stderr, "cmd->name: %s, pid=%d, ppid=%d\n", cmd->name, getpid(), getppid());
	ft_dup(cmd);
	// fprintf(stderr, "cmd->fds:%d, %d\n", cmd->fd[0], cmd->fd[1]);
	if (cmd->fd[0] == -1 || cmd->fd[1] == -1)
		fprintf(stderr, "ERROR: cmd->fd[0]=%d, cmd->fd[1]=%d\n", cmd->fd[0], cmd->fd[1]);
	close_pipes2(cmd, 42);
	if (cmd->name)
		cmd->name = get_path(cmd->name, cmd->envp);
	if (cmd->name)
		execve(cmd->name, cmd->argv, cmd->envp);
	ft_msg("Command not found", cmd->name);
	if (cmd->argv)
		ft_free_tab_str(cmd->argv, -1);
	dispatch_exit(cmd, 127);
}

void init_fd(t_cmd *cmd)
{
	if (!cmd->next)
	{
		open_files(cmd);
		return;
	}
	open_pipes(cmd);
}

int ft_exec(t_cmd *cmd)
{
	t_cmd *tmp;

	if (!cmd)
		return (1);
	tmp = cmd;

	init_fd(tmp);
	ft_print_cmd(cmd);
	while (tmp && tmp->pid)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			dispatch_exit(tmp, 8);
		if (tmp->pid == 0)
			fprintf(stderr, "CHILD   %d\n", getpid());
		else
			fprintf(stderr, "PARENT  %d\n", getpid());
		if (!tmp->pid)
			child(tmp);
		tmp = tmp->next;
	}
	//ft_print_cmd(cmd);
	fprintf(stderr, "___%d___\n", getpid());
	sleep(20);
	dispatch_exit(cmd, 777);
	fprintf(stderr, "_=_%d_=_\n", getpid());
	sleep(20);
	return (0);
}
