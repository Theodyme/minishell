/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:41:16 by flplace           #+#    #+#             */
/*   Updated: 2023/10/24 15:57:46 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_pwd(t_cmd *cmd)
{
	char *tofree;

	if (cmd->args_list->next && cmd->args_list->next->str
		&& cmd->args_list->next->str[0] == '-')
	{
		if (cmd->args_list->next->str[1] == '-' && cmd->args_list->next->str[3])
		{
			printf(TRITON "pwd: --: invalid option\n");
			return (2);
		}
		printf(TRITON "pwd: %s: invalid option\n", cmd->args_list->next->str);
		return (2);
	}
	tofree = getcwd(NULL, 0);
	if (tofree == NULL)
	{
		printf(TRITON DIR_ERR);
		return (1);
	}
	ft_putendl_fd(tofree, cmd->fd[1]);
	ft_putendl_fd("\n", cmd->fd[1]);
	free(tofree);
	return (0);
}
