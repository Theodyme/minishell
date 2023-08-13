/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:55:51 by flplace           #+#    #+#             */
/*   Updated: 2023/08/13 21:59:38 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_hello(t_cmd *cmd)
{
	struct s_arg	*tmp;

	if (!cmd->args_list->next->str)
	{
		printf("\033[34mᴛʀɪᴛᴏɴ\033[0m: Who are you talking to?\n");
		return (1);
	}
	tmp = cmd->args_list->next;
	if (ft_strcmp(ft_str_tolower(tmp->str), "triton") != 0
		&& ft_strcmp(ft_str_tolower(tmp->str), "triton!") != 0)
		printf("\033[34mᴛʀɪᴛᴏɴ\033[0m: Who are you talking to?\n");
	else
	{
		// printf(HELLO_1);
		// printf(HELLO_2);
		// printf(HELLO_3);
		// printf(HELLO_4);
		// printf(HELLO_5);
		// printf(HELLO_6);
		// printf(HELLO_7);
		// printf(HELLO_8);
		// printf(HELLO_9);
	}
	return (0);
}
