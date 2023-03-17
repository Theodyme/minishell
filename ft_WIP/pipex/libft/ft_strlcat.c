/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:41:10 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/07 18:41:11 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	ls;
	size_t	ld;

	i = 0;
	if (src == NULL || dest == NULL)
		return (0);
	ls = ft_strlen(src);
	ld = ft_strlen(dest);
	if (n <= ld)
		return (n + ls);
	while (src[i] != '\0' && i + ld + 1 < n)
	{
		dest[i + ld] = src[i];
		i++;
	}
	dest[i + ld] = '\0';
	dest[--n] = '\0';
	return (ld + ls);
}
