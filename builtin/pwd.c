/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:41:16 by flplace           #+#    #+#             */
/*   Updated: 2023/10/29 18:09:16 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_pwd(t_cmd *cmd)
{
	char	*tofree;
	t_arg	*arg;

	arg = cmd->args_list->next;
	if (arg && arg->str && arg->str[0] == '-')
	{
		if (arg->str[1] && arg->str[1] == '-')
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
	printf("%s\n", tofree);
	free(tofree);
	return (0);
}
