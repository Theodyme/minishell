/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:47:09 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/07 16:42:22 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curs;
	t_list	*nx;

	curs = *lst;
	nx = *lst;
	while (curs)
	{
		nx = curs->next;
		ft_lstdelone(curs, *del);
		curs = nx;
	}
	*lst = NULL;
}
