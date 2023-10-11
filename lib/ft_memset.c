/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:42:28 by flplace           #+#    #+#             */
/*   Updated: 2023/02/02 13:48:18 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cc;

	if (!b)
		return (NULL);
	cc = (unsigned char *)b;
	while (len--)
		cc[len] = (unsigned char)c;
	b = (void *)cc;
	return (b);
}
