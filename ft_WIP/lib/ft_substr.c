/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:29:58 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/30 17:30:06 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
