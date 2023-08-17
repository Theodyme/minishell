/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:07:52 by flplace           #+#    #+#             */
/*   Updated: 2023/08/17 07:32:27 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_only_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_isoperand(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	ft_bltin_exit(t_cmd *cmd)
{
	int		i;
	t_arg	*tmp;

	i = 0;
	tmp = cmd->args_list->next;
	if (!tmp->str)
		ft_free_n_exit(cmd, 0);
	if (tmp->next->str)
	{
		printf(TRITON "too many arguments.\n");
		return (1);
	}
	if (ft_isoperand(tmp->str[i]) == 1)
		i++;
	if (ft_is_only_num(tmp->str + i) == 1)
	{
		ft_free_n_exit(cmd, (ft_atoi(tmp->str)));
	}
	else
		printf(TRITON "numeral argument needed.\n");
	return (1);
}
