/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:54:27 by mabimich          #+#    #+#             */
/*   Updated: 2022/07/18 22:15:04 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pick(char const *s, char c, size_t p)
{
	char	**in;
	char	*out;
	size_t	i;

	if (!s || !c)
		return (NULL);
	i = 0;
	in = ft_split(s, c);
	out = ft_strdup(in[p]);
	while (in[i])
		free(in[i++]);
	free(in);
	return (out);
}
