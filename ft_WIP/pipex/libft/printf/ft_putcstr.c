/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:50:41 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/15 20:33:28 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putcstr(char *str, char c)
{
	size_t	i;

	i = ft_strclen(str, c);
	if (!str)
		return (0);
	write(1, str, i);
	return (i);
}
