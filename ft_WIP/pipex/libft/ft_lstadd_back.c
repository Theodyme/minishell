/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:59:36 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/02 17:22:30 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lt;

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
