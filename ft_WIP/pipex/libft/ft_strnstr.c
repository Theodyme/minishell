/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:22:45 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/02 18:22:47 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *m, const char *a, size_t n)
{
	size_t	la;
	size_t	i;
	size_t	j;

	if (m == NULL || a == NULL)
		return (NULL);
	la = ft_strlen(a);
	if (la == 0)
		return ((char *)(m));
	i = -1;
	while (m[++i] && i < n)
	{
		if (m[i] == a[0])
		{
			j = 0;
			while (m[i + j] && a[j] && m[i + j] == a[j] && i + j < n)
				j++;
			if (a[j] == '\0')
				return ((char *)(m + i));
		}
	}
	return (NULL);
}
