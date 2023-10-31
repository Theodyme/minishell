/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:25:43 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/31 09:04:21 by mabimich         ###   ########.fr       */
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
	if (tmp[0] > 0)
	{
		ft_close_fd(cmd->fd[0]);
		cmd->fd[0] = tmp[0];
	}
	else if (tmp[1] > 0)
	{
		ft_close_fd(cmd->fd[1]);
		cmd->fd[1] = tmp[1];
	}
	if (redir->type != HEREDOC && (cmd->fd[0] == -1 || cmd->fd[1] == -1))
	{
		ft_msg(redir->file, strerror(errno));
		close_pipes(cmd);
		if (!(cmd->bltn && (!cmd->head->next)))
			ft_free_n_exit(cmd, 1);
	}
}

void	init_fd(t_cmd *cmd)
{
	if (cmd->fd[0] == STDIN_FILENO)
		cmd->fd[0] = dup(STDIN_FILENO);
	if (cmd->fd[1] == STDOUT_FILENO)
		cmd->fd[1] = dup(STDOUT_FILENO);
}

void	open_files(t_cmd *cmd)
{
	t_redir	*redir;
	int		tmp[2];

	tmp[0] = -2;
	tmp[1] = -2;
	init_fd(cmd);
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

void	init_child(t_cmd *cmd)
{
	ft_envlist_to_array(cmd);
	open_files(cmd);
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close_pipes(cmd);
}
