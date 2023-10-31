/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:25:43 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/31 01:05:17 by mabimich         ###   ########.fr       */
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

void	close_protection(t_cmd *cmd, t_redir *redir, int *tmp)
{
	if (tmp[0])
	{
		close(cmd->fd[0]);
		cmd->fd[0] = tmp[0];
	}
	else if (tmp[1])
	{
		close(cmd->fd[1]);
		cmd->fd[1] = tmp[1];
	}
	if (cmd->fd[0] == -1 || cmd->fd[1] == -1)
	{
		ft_msg(redir->file, strerror(errno));
		close_pipes(cmd);
		ft_free_n_exit(cmd->head, 1);
	}
}

void	open_files(t_cmd *cmd)
{
	t_redir	*redir;
	int		tmp[2];

	tmp[0] = 0;
	tmp[1] = 0;
	redir = cmd->redir;
	if (g_status == 130 || g_status == 131)
		g_status = 0;
	while (cmd && redir)
	{
		if (redir->type == REDIR_IN)
			tmp[0] = open(redir->file, O_RDONLY);
		else if (redir->type == HEREDOC)
			tmp[0] = here_doc(redir);
		else if (redir->type == REDIR_OUT)
			tmp[1] = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			tmp[1] = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		close_protection(cmd, redir, tmp);
		redir = redir->next;
	}
	if (g_status == 130 || g_status == 131)
		dispatch_exit(cmd, g_status);
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

void	close_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd->head;
	while (tmp)
	{
		if (tmp->fd[0] != STDIN_FILENO && tmp->fd[0] != -1)
			close(tmp->fd[0]);
		if (tmp->fd[1] != STDOUT_FILENO && tmp->fd[1] != -1)
			close (tmp->fd[1]);
		tmp = tmp->next;
	}
}

void	init_child(t_cmd *cmd)
{
	ft_envlist_to_array(cmd);
	open_files(cmd);
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close_pipes(cmd);
}
