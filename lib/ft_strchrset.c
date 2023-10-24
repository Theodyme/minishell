/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:15:26 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/24 15:18:01 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchrset(const char *s, char *c)
{
	int	i;
	int	j;

	i = -1;
	if (s == NULL || c == NULL)
		return (NULL);
	while (s[++i])
	{
		j = -1;
		while (c[++j])
			if (s[i] == c[j])
				return ((char *)&(s[i]));
	}
	return (NULL);
}
