/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:48:26 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/07 16:57:17 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_c_isin_set(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] && set[i] != c)
		i++;
	if (set[i])
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	char	*new_s;
	int		l;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	l = ft_strlen(s1) + 1;
	while (--l && ft_c_isin_set(s1[start], set))
		start++;
	while (l && ft_c_isin_set(s1[start + l - 1], set))
		l--;
	new_s = ft_substr(s1, start, l);
	if (!new_s)
		return (NULL);
	return (new_s[l] = '\0', new_s);
}
