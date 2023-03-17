/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:52:27 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/07 13:23:14 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*srcc;
	unsigned char	*dstc;
	size_t			i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (dst);
	srcc = (unsigned char *)src;
	dstc = (unsigned char *)dst;
	if (srcc < dstc)
		while (n--)
			dstc [n] = srcc[n];
	else
	{
		while (i < n)
		{
			dstc[i] = srcc[i];
			i++;
		}
	}
	return (dst);
}
