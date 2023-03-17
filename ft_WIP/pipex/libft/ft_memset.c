/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:51:11 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/07 18:26:38 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cc;

	if (!b)
		return (NULL);
	cc = (unsigned char *)b;
	while (len--)
		cc[len] = (unsigned char)c;
	b = (void *)cc;
	return (b);
}
