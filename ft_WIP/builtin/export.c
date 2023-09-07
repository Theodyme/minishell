/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:13:33 by flplace           #+#    #+#             */
/*   Updated: 2023/09/07 13:25:19 by flplace          ###   ########.fr       */
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

int	ft_export_valid(t_arg *args)
{
	int		i;
	t_arg	*tmp;

	tmp = args->next;
	i = 0;
	if (ft_is_equal(tmp) == 1)
		return (0);
	while (tmp && tmp->str)
	{
		while (tmp->str[i])
		{
			printf("pouet\n");
			if (!ft_isalpha(tmp->str[i]) && tmp->str[i] != '=')
			{
				printf(TRITON "export: '%s': not a valid identifier\n",
					tmp->str);
				return (0);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_bltin_export(t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*needle;
	char	*key;
	char	*value;

	if (ft_array_cntr(cmd->argv) != 2 || ft_export_valid(cmd->args_list) == 0)
		return (1);
	key = ft_split_key(cmd->argv[1]);
	value = ft_split_value(cmd->argv[1]);
	needle = ft_key_finder(&(cmd->envt), key);
	if (!needle)
	{
		tmp = ft_key_add(&(cmd->envt), key, value);
		if (tmp && ft_strcmp(tmp->key, key) == 0
			&& ft_strcmp(tmp->value, value) == 0)
			return (ft_key_freer(key, value));
	}
	if (needle != NULL && (ft_strcmp(needle->value, value) != 0))
	{
		free(needle->value);
		needle->value = ft_strdup(value);
	}
	ft_key_freer(key, value);
	return (0);
}
