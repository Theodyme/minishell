/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:41:28 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/07 18:41:29 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL || n == 0)
		return (0);
	while (s1[i] == s2[i])
	{
		if ((s1[i] == '\0' && s2[i] == '\0') || n < i + 2)
			return (0);
		i++;
	}
	if (s1[i] == '\0')
		return (-(unsigned char)s2[i]);
	if (s2[i] == '\0')
		return ((unsigned char)s1[i]);
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}
