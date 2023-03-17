/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:50:55 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/07 15:36:17 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	char	*str;

	if (!s)
		return (NULL);
	l = (size_t)ft_strlen((char *) &s[start]);
	if (len < l)
		l = len;
	str = (char *)ft_calloc(sizeof(char), (l + 1));
	if (!str)
		return (NULL);
	if (start > ft_strlen(s))
		return (str);
	str = ft_memmove(str, &s[start], l);
	return (str);
}
