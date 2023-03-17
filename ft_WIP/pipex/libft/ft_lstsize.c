/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:49:34 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/07 13:14:03 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*lt;

	if (!lst)
		return (0);
	i = 1;
	lt = lst;
	while (lt->next != NULL)
	{
		lt = lt->next;
		i++;
	}
	return (i);
}
