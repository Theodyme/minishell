/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:59 by flplace           #+#    #+#             */
/*   Updated: 2023/02/23 17:09:57 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env		*ft_bltin_unset(t_cmd_div *div)
{
	t_env	*parse;
	t_env	*rm;
	char	*key;

	(void)div;
	parse = div->envt;
	key = ft_strdup(div->args[1]);
	if (ft_strcmp(parse->key, key) == 0)
	{
		div->envt = parse->next;
		rm = parse;
		parse = div->envt;
	}
	else
	{
		while (parse->next && (ft_strcmp(parse->next->key, key) != 0))
			parse = parse->next;
		if ((!parse->next) || ((!parse->next) && (ft_strcmp(parse->key, key) == 0)))
			return (NULL);
		rm = parse->next;
		parse->next = rm->next;
	}
	ft_key_remove(rm);
	if (parse->next == NULL)
		return (NULL);
	return (parse);
}
