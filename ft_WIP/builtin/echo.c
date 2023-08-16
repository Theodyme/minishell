/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:54:46 by flplace           #+#    #+#             */
/*   Updated: 2023/08/16 19:25:09 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_echo(t_cmd *cmd)
{
	int				stdout_copy;
	struct s_arg	*tmp;

	if (!cmd->args_list->next->str)
	{
		write(1, "\n", 1);
		return (1);
	}
	stdout_copy = dup(STDOUT_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	tmp = cmd->args_list->next;
	if (ft_strcmp(tmp->str, "-n") == 0)
		tmp = tmp->next;
	while (cmd->args_list && tmp)
	{
		ft_putendl_fd((tmp->str), 1);
		if (tmp->next && tmp->next->str)
			ft_putendl_fd(" ", 1);
		tmp = tmp->next;
	}
	if (ft_strcmp(cmd->args_list->next->str, "-n") != 0)
		write(1, "\n", 1);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	return (1);
}
