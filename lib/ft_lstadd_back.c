/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:44:45 by flplace           #+#    #+#             */
/*   Updated: 2023/02/02 13:46:30 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_token **alst, t_token *new)
{
	t_token	*lt;

	if (!new || !alst)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	lt = ft_lstlast(*alst);
	lt->next = new;
}
