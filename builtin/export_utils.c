/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:45:48 by flplace           #+#    #+#             */
/*   Updated: 2023/10/23 17:35:05 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int n)
{
	if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z'))
		return (1);
	return (0);
}

int	ft_is_equal(t_arg *args)
{
	if (args->str[0] == '=')
	{
		if (args->str[1] == '\0')
		{
			if (!args->next->str)
			{
				printf(TRITON "export: '=': not a valid identifier\n");
				return (1);
			}
		}
	}
	return (0);
}

void	ft_loop_export(t_cmd *cmd, int is_ok)
{
	t_arg	*tmp;
	t_arg	*prev;

	tmp = cmd->args_list->next;
	prev = cmd->args_list;
	while (tmp && tmp->str)
	{
		if (ft_char_valid(tmp) != 1)
		{
			if (is_ok == 0)
				printf(TRITON "export: '%s': not a valid identifier\n",
					tmp->str);
			prev->next = tmp->next;
			free(tmp->str);
			free(tmp);
			tmp = prev->next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
