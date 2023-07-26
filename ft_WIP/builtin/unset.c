/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:59 by flplace           #+#    #+#             */
/*   Updated: 2023/07/26 16:48:29 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_unset(t_cmd *cmd)
{
	t_env	*prev;
	t_env	*current;
	char	*key;

	prev = NULL;
	current = cmd->envt;
	key = ft_strdup(cmd->argv[1]);
	if (ft_strcmp(key, "PWD") == 0)
		return (free(key), 1);
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				cmd->envt = current->next;
			ft_key_remove(current);
			free(key);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (free(key), 1);
}
