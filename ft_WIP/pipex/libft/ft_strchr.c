/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:55:58 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/06 15:09:45 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	if (s == NULL)
		return (NULL);
	while (s[++i] != (char)c)
		if (s[i] == '\0')
			return (NULL);
	return ((char *)&(s[i]));
}
