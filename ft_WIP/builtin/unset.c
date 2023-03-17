/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:59 by flplace           #+#    #+#             */
/*   Updated: 2023/03/17 16:26:44 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_bltin_unset(t_cmd *cmd)
{
	t_env	*parse;
	t_env	*rm;
	char	*key;

	parse = cmd->envt;
	key = ft_strdup(cmd->args[0]);
	printf("key = %s\n", key);
	printf("parse->key = %s\n", parse->key);
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
			return (1);
		rm = parse->next;
		parse->next = rm->next;
	}
	ft_key_remove(rm);
	if (parse->next == NULL)
		return (1);
	return (0);
}
