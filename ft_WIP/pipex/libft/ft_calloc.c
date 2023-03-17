/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:15:24 by mabimich          #+#    #+#             */
/*   Updated: 2022/06/22 18:19:49 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int	*tab;

	tab = (void *)malloc(size * count);
	if (!tab)
		return (NULL);
	ft_bzero(tab, size * count);
	return (tab);
}
