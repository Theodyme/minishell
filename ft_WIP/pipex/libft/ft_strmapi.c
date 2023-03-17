/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:04:04 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/02 18:08:04 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new_s;

	i = -1;
	if (s == NULL)
		return (NULL);
	new_s = (char *)malloc((ft_strlen(s) + 1) * sizeof(*s));
	if (new_s == NULL)
		return (NULL);
	while (s[++i])
		new_s[i] = f(i, s[i]);
	new_s[i] = '\0';
	return (new_s);
}
