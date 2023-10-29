/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:54:46 by flplace           #+#    #+#             */
/*   Updated: 2023/10/29 17:50:18 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_has_nflag(char *str)
{
	int i;

	i = 0;
	if (str && str[i] && str[i] == '-')
	{
		i++;
		while (str[i] && (str[i] == 'n'))
			i++;
		if (str[i])
			return (0);
		return (1);
	}
	return (0);
}

void ft_echo_print(t_arg *tmp)
{
	while (tmp)
	{
		write(1, tmp->str, ft_strlen(tmp->str));
		if (tmp->next && tmp->next->str)
			write(1, " ", 1);
		tmp = tmp->next;
	}
	return;
}

int ft_bltin_echo(t_cmd *cmd)
{
	struct s_arg *tmp;
	int flag;

	flag = 0;
	if (!cmd->args_list->next)
	{
		write(1, "\n", 1);
		return (0);
	}
	tmp = cmd->args_list->next;
	while (cmd->args_list && tmp)
	{
		if (ft_has_nflag(tmp->str) == 0)
			ft_echo_print(tmp);
		else
			flag++;
		tmp = tmp->next;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
