/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:42:26 by flplace           #+#    #+#             */
/*   Updated: 2023/02/02 13:49:46 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	int	*tab;

	tab = (void *)malloc(size * count);
	if (!tab)
		return (NULL);
	ft_memset(tab, 0, size * count);
	return (tab);
}
