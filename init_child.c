/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:25:43 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/17 16:00:21 by flplace          ###   ########.fr       */
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

void	open_files(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = cmd;
	redir = tmp->redir;
	if (g_status == 130)
		g_status = 0;
	while (cmd && redir)
	{
		if (redir->type == REDIR_IN)
			cmd->fd[0] = open(redir->file, O_RDONLY);
		else if (redir->type == HEREDOC)
			cmd->fd[0] = here_doc(redir);
		else if (redir->type == REDIR_OUT)
			cmd->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			cmd->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fd[0] == -1 || cmd->fd[1] == -1)
		{
			ft_msg(redir->file, strerror(errno));
			ft_free_n_exit(cmd->head, 1);
		}
		redir = redir->next;
	}
	if (g_status == 131 || g_status == 130)
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

void	init_child(t_cmd *cmd)
{
	ft_envlist_to_array(cmd);
	open_files(cmd);
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close_pipes(cmd);
}
