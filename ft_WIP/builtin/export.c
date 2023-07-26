/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:13:33 by flplace           #+#    #+#             */
/*   Updated: 2023/07/26 16:00:21 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_export(t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*needle;
	char	*key;
	char	*value;

	if (ft_array_cntr(cmd->argv) != 2)
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
	return (1);
}
