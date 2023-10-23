/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:13:33 by flplace           #+#    #+#             */
/*   Updated: 2023/10/23 14:20:29 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_char_valid(char *str, int i)
{
	if ((!ft_isalpha(str[i])
			&& !ft_is_in_charset(str[i], "0123456789_="))
		|| (str[i] == '=' && str[i + 1] == '\0'))
	{
		printf(TRITON "export: '%s': not a valid identifier\n",
			str);
		return (0);
	}
	return (1);
}

int	ft_export_valid(t_arg *args)
{
	int		i;
	t_arg	*tmp;
	int		equal;
	int		arg_cntr;

	arg_cntr = ft_args_cntr(args) - 1;
	tmp = args->next;
	equal = 0;
	while (tmp && tmp->str)
	{
		i = 0;
		while (tmp->str[i])
		{
			if (ft_char_valid(tmp->str, i) == 0)
				return (0);
			if (tmp->str[i] == '=')
				equal += 1;
			i++;
		}
		tmp = tmp->next;
	}
	if (equal != arg_cntr)
		return (0);
	return (1);
}

int	ft_export_args(t_cmd *cmd)
{
	if (ft_args_cntr(cmd->args_list) == 1)
		return (1);
	if (cmd->args_list->next->str[0] == '-')
	{
		printf(TRITON "export: '%s': invalid option\n",
			cmd->args_list->next->str);
		return (1);
	}
	if (ft_is_equal(cmd->args_list->next) == 1)
		return (1);
	if (ft_export_valid(cmd->args_list) == 0)
		return (1);
	return (0);
}

int	ft_exporting(char *arg, t_cmd *cmd)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	t_env	*needle;

	key = ft_split_key(arg);
	value = ft_split_value(arg);
	needle = ft_key_finder(cmd->envt, key);
	if (!needle)
	{
		tmp = ft_key_add(cmd->envt, key, value);
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

int	ft_bltin_export(t_cmd *cmd)
{
	int		check;
	int		ret;
	t_arg	*arg;

	ret = 0;
	check = ft_export_args(cmd);
	if (check)
	{
		return (check);
	}
	arg = cmd->args_list->next;
	while (arg && arg->str)
	{
		ret = ft_exporting(arg->str, cmd);
		arg = arg->next;
	}
	return (ret);
}
