/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_full.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:25:32 by mabimich          #+#    #+#             */
/*   Updated: 2022/07/17 20:28:40 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_full(size_t count, size_t size)
{
	int	*tab;

	tab = (void *)malloc(size * count);
	if (!tab)
		return (NULL);
	ft_memset(tab, 1, size * count);
	return (tab);
}
