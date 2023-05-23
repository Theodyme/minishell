/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:59 by flplace           #+#    #+#             */
/*   Updated: 2023/05/23 19:03:29 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_bltin_unset(t_cmd *cmd)
{
	t_env	*parse;
	t_env	*rm;
	char	*key;

	parse = cmd->envt;
	key = ft_strdup(cmd->argv[1]);
	if (ft_strcmp(key, "PWD") == 0)
		return (1);
	if (ft_strcmp(parse->key, key) == 0)
	{
		cmd->envt = parse->next;
		rm = parse;
		parse = cmd->envt;
	}
	else
	{
		while (parse->next && (ft_strcmp(parse->next->key, key) != 0))
			parse = parse->next;
		if ((!parse->next) || ((!parse->next) && (ft_strcmp(parse->key, key) == 0)))
		{
			free(key);
			return (1);
		}
		rm = parse->next;
		parse->next = rm->next;
	}
	free(key);
	ft_key_remove(rm);
	if (parse->next == NULL)
		return (1);
	return (0);
}
