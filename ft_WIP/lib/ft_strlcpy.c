/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:43:46 by flplace           #+#    #+#             */
/*   Updated: 2023/03/01 19:01:38 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = -1;
	if (!(size))
		return (ft_strlen(src));
	while (src[++i] && size > i + 1)
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}
