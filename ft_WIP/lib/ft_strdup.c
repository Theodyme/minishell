/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:52:16 by flplace           #+#    #+#             */
/*   Updated: 2023/03/16 16:47:14 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *src)
{
	int		l;
	char	*str;

	if (src == NULL)
		return (NULL);
	l = ft_strlen((char *)src);
	str = (char *)ft_calloc(sizeof(*str), (l + 1));
	if (str == NULL)
		return (NULL);
	str = ft_strcpy(str, src);
	return (str);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*str;

	if (src == NULL)
		return (NULL);
	str = (char *)ft_calloc(sizeof(*str), (n + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, src, n + 1);
	return (str);
}
