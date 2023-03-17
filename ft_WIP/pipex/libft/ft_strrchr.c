/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:24:00 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/06 15:09:31 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (s == NULL)
		return (NULL);
	i = ft_strlen((char *)s);
	if ((char)c == '\0')
		return ((char *)&s[i]);
	if (i == 0)
		return (NULL);
	while (s[--i] != (char)c)
		if (i == 0)
			return (0);
	return ((char *)&(s[i]));
}
