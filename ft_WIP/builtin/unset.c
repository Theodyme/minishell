/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:59 by flplace           #+#    #+#             */
/*   Updated: 2023/02/10 17:32:22 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env		*ft_bltin_unset(t_env **envt, char *needle)
{
	t_env	*parse;
	t_env	*rm;

	parse = (*envt);
	while (ft_strcmp(parse->next->key, needle) != 0)
		parse = parse->next;
	rm = parse->next;
	parse->next = rm->next;
	ft_key_remove(rm);
	if (parse->next == NULL)
		return (NULL);
	return (parse);
}
