/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:45:48 by flplace           #+#    #+#             */
/*   Updated: 2023/10/24 19:19:00 by flplace          ###   ########.fr       */
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
				return (0);
			}
		}
	}
	return (1);
}
char	*trim_to_export(char *value)
{
	char	*tmp;
	char	*output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	output = malloc(sizeof(char) * ft_strlen(value) + 1);
	tmp = ft_strtrim(value, C_BLANK);
	if (!tmp || !output)
		return (ft_strdup(" "));
	while (tmp && tmp[i] && output)
	{
		if (ft_is_in_charset(tmp[i], C_BLANK))
		{
			output[j++] = ' ';
			while (ft_is_in_charset(tmp[i], C_BLANK))
				i++;
		}
		else
			output[j++] = tmp[i++];
	}
	output[j] = '\0';
	free(tmp);
	return (output);
}

int	ft_loop_export(t_cmd *cmd, int is_ok)
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
			if (is_ok == 0 && tmp && !tmp->str)
				return (1);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (0);
}
