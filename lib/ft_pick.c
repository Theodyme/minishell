/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:54:27 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/17 21:21:40 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
