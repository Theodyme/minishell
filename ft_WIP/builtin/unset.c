/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:59 by flplace           #+#    #+#             */
/*   Updated: 2023/02/17 18:18:48 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env		*ft_bltin_unset(t_env **envt, char *key)
{
	t_env	*parse;
	t_env	*rm;

	parse = (*envt);
	if (ft_strcmp(parse->key, key) == 0)
	{
		(*envt) = parse->next;
		rm = parse;
		parse = (*envt);
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
