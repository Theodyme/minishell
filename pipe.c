/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:03:43 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/31 09:04:28 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (tmp->fd[0] != STDIN_FILENO)
			ft_close_fd(tmp->fd[0]);
		if (tmp->fd[1] != STDOUT_FILENO)
			ft_close_fd(tmp->fd[1]);
		tmp = tmp->next;
	}
}
