/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:54:46 by flplace           #+#    #+#             */
/*   Updated: 2023/09/01 16:58:35 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_has_nflag(char *str)
{
	int	i;

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

int	ft_bltin_echo(t_cmd *cmd)
{
	struct s_arg	*tmp;
	int				flag;

	flag = 0;
	if (!cmd->args_list->next->str)
		return (0);
	tmp = cmd->args_list->next;
	while (cmd->args_list && tmp)
	{
		if (ft_has_nflag(tmp->str) == 0)
		{
			while (tmp)
			{
				ft_putendl_fd((tmp->str), 1);
				if (tmp->next && tmp->next->str)
					ft_putendl_fd(" ", 1);
				tmp = tmp->next;
			}
		}
		else if (ft_has_nflag(tmp->str) == 1)
		{
			flag++;
			tmp = tmp->next;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
