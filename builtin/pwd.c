/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:41:16 by flplace           #+#    #+#             */
/*   Updated: 2023/10/23 16:19:45 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_pwd(t_cmd *cmd)
{
	t_env	*pwd;

	pwd = NULL;
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
	pwd = ft_key_finder(cmd->envt, "PWD");
	if (pwd == NULL || !pwd->value)
	{
		ft_putendl_fd(getcwd(NULL, 0), cmd->fd[1]);
		ft_putendl_fd("\n", cmd->fd[1]);
		return (0);
	}
	ft_putendl_fd(pwd->value, cmd->fd[1]);
	ft_putendl_fd("\n", cmd->fd[1]);
	return (0);
}
