/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:03:29 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/04 19:39:36 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = -1;
	if (!(size))
		return (ft_strlen(src));
	while (src[++i] && size > i + 1)
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}
