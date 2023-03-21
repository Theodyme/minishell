/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:28:34 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/21 21:38:40 by mabimich         ###   ########.fr       */
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
	if (ft_strcmp(cmd->name, "ls") == 0)
		sleep(1);
	if (ft_strcmp(cmd->name, "wc") == 0)
		sleep(2);
	while (head)
	{
		printf("head->name=%s, head->fd[0]=%d, head->fd[1]=%d\n", head->name, head->fd[0], head->fd[1]);
		head = head->next;
	}
	printf("\n");
}

void ft_dup(t_cmd *cmd)
{
	ft_check_fd(cmd);
	printf("DUP\nchild: cmd->name=%s, fd[0]=%d, fd[1]=%d\n", cmd->name, cmd->fd[0], cmd->fd[1]);
	if (cmd->fd[0] == -1)
		dispatch_exit(cmd, 555);
	else if (cmd->fd[1] == -1)
		dispatch_exit(cmd, 666);
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	printf("DUP DONE for cmd->name=%s\n", cmd->name);
	//sleep(10);
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
	while (tmp->next)
	{
		tmp->fd[0] = tmp->fd[1];
		tmp->fd[1] = tmp->next->fd[0];
		tmp = tmp->next;
	}
	tmp->fd[1] = STDOUT_FILENO;
	// tmp = cmd;
	// printf("CHECK_FD: tmp->fd[0]=%d, tmp->fd[1]=%d\n", tmp->fd[0], tmp->fd[1]);
	// tmp = tmp->next;
	// printf("CHECK_FD: tmp->fd[0]=%d, tmp->fd[1]=%d\n", tmp->fd[0], tmp->fd[1]);
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
	// int j = 0;

	tmp = cmd->head;
	close(3);
	close(4);
	return ; ///////////////////////////////////////////////////
	while (tmp)
	{
		fprintf(stderr, "%d: close_pipes2: tmp->name=%s, tmp->fd[0]=%d, tmp->fd[1]=%d____\n", getpid(), tmp->name, tmp->fd[0], tmp->fd[1]);
		if (tmp->fd[0] == -1 && tmp->fd[1] == -1)
			fprintf(stderr, "+ERROR:tmp->fd[0] == -1 && tmp->fd[1] == -1\n");
		if (cmd->fd[0] == -1 && cmd->fd[1] == -1)
			fprintf(stderr, "+ERROR:cmd->fd[0] == -1 && cmd->fd[1] == -1\n");
		if (cmd->fd[0] == -1 && cmd->fd[1] != -1)
			close(tmp->fd[1]);
		// if (tmp->fd[0] != -1 && tmp->fd[0] != cmd->fd[0] && tmp->fd[0] != cmd->fd[1])
		// {
		// 	fprintf(stderr," __%d %d__%s garde ouvert: tmp->fd[0]=%d\n", i, j, cmd->name, cmd->fd[0]);
		// 	fprintf(stderr, "close: tmp->fd[0]=%d\n", tmp->fd[0]);
		// 	close(tmp->fd[0]);
		// }	
		// if (tmp->fd[1] != -1 && tmp->fd[1] != cmd->fd[1] && tmp->fd[1] != cmd->fd[0])
		// {
		// 	fprintf(stderr, "__%d %d__%s garde ouvert: tmp->fd[1]=%d\n", i, j, cmd->name, cmd->fd[1]);
		// 	fprintf(stderr, "close: tmp->fd[1]=%d\n", tmp->fd[1]);
		// 	close(tmp->fd[1]);
		// }
		tmp = tmp->next;
		i++;
	}
	fprintf(stderr, "end closing pipe\n");
}

void child(t_cmd *cmd)
{
	ft_envlist_to_array(cmd);

	// printf("child: cmd->name=%s, cmd->envp=%s\n", cmd->name, cmd->envp[1]);
	fprintf(stderr, "cmd->name: %s, pid=%d, ppid=%d\n", cmd->name, getpid(), getppid());
//	sleep(10);
	ft_dup(cmd);
	fprintf(stderr, "cmd->fds:%d, %d\n", cmd->fd[0], cmd->fd[1]);
	// if (cmd->fd[0] != -1)
	// 	close(cmd->fd[0]);
	// if (cmd->fd[1] != -1)
	// 	close(cmd->fd[1]);
	if (cmd->fd[0] == -1 || cmd->fd[1] == -1)
		fprintf(stderr, "ERROR: cmd->fd[0]=%d, cmd->fd[1]=%d\n", cmd->fd[0], cmd->fd[1]);
	//sleep(10);
	close_pipes2(cmd, 42);
	//sleep(10);
	// printf("before get_path: cmd->name=%s, cmd->envp=%s\n", cmd->name, cmd->envp[0]);
	if (cmd->name)
		cmd->name = get_path(cmd->name, cmd->envp);
	// printf("ret after get_path:cmd->name = %s, cmd->argv[0] = %s\n", cmd->name, cmd->argv[0]);
	//sleep(20);
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
		return;
	open_pipes(cmd);
	//open_files(cmd);
}

int ft_exec(t_cmd *cmd)
{
	t_cmd *tmp;

	if (!cmd)
		return (1);
	tmp = cmd;
	printf("BEFORE INIT_FD\n");
	printf("%d\n", getpid());
	ft_print_cmd(cmd);
	sleep(15);
	init_fd(tmp);
	//sleep(5);
	ft_print_cmd(cmd);
	while (tmp && tmp->pid)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			dispatch_exit(tmp, 8);
		if (tmp->pid == 0)
			printf("CHILD\n");
		else
			printf("PARENT\n");
		if (!tmp->pid)
			child(tmp);
		tmp = tmp->next;
	}
	//ft_print_cmd(cmd);
	dispatch_exit(cmd, 777);
	return (0);
}
