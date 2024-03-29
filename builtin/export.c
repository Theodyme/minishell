/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:13:33 by flplace           #+#    #+#             */
/*   Updated: 2023/10/25 22:12:09 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_char_valid(t_arg *tmp)
{
	int	equal;
	int	i;

	equal = 0;
	i = 0;
	while (tmp->str[i])
	{
		if (((i == 0 && tmp->str[i] == '=')) || (!ft_isalpha(tmp->str[i])
				&& !ft_is_in_charset(tmp->str[i], "0123456789_=") && equal == 0)
			|| (tmp->str[i] == '=' && tmp->str[i + 1] == '\0'))
			return (0);
		else if (tmp->str[i] == '=')
			equal += 1;
		i++;
	}
	return (equal);
}

int	ft_export_valid(t_cmd *cmd)
{
	t_arg	*tmp;
	int		is_ok;
	int		args_cntr;

	args_cntr = ft_args_cntr(cmd->args_list);
	tmp = cmd->args_list->next;
	is_ok = 0;
	while (tmp && tmp->str)
	{
		if (ft_char_valid(tmp) == 1)
			is_ok++;
		tmp = tmp->next;
	}
	if (is_ok != 0 && is_ok == args_cntr)
		return (1);
	if (ft_loop_export(cmd, is_ok) == 1)
		return (0);
	return (1);
}

int	ft_export_args(t_cmd *cmd)
{
	if (ft_args_cntr(cmd->args_list) == 1)
		return (1);
	if (cmd->args_list->next->str[0] == '-')
	{
		printf(TRITON "export: `%s': invalid option\n",
			cmd->args_list->next->str);
		return (2);
	}
	if (ft_is_equal(cmd->args_list->next) == 0)
		return (1);
	if (ft_export_valid(cmd) == 0)
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
			return (ft_key_freer(key, value), 0);
	}
	if (needle != NULL && (ft_strcmp(needle->value, value) != 0))
	{
		free(needle->value);
		needle->value = value;
		if (!needle->value)
			return (ft_key_remove(needle), 1);
		free(key);
		return (0);
	}
	return (ft_key_freer(key, value), 0);
}

int	ft_bltin_export(t_cmd *cmd)
{
	int		check;
	int		ret;
	t_arg	*arg;

	ret = 0;
	check = ft_export_args(cmd);
	if (check)
		return (check);
	arg = cmd->args_list->next;
	while (arg && arg->str)
	{
		ret = ft_exporting(arg->str, cmd);
		arg = arg->next;
	}
	return (ret);
}
