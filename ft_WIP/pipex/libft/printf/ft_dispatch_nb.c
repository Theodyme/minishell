/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 20:54:43 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/15 20:54:49 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dispatch_nb(unsigned long long nbr, char c)
{
	if (c == 'd' || c == 'i')
		return (ft_putnbr((int)nbr, 1));
	if (c == 'u')
		return (ft_putn_b((unsigned int)nbr, "0123456789", 1));
	if (c == 'p')
		return (write(1, "0x", 2), ft_putn_b(nbr, "0123456789abcdef", 1) + 2);
	if (c == 'x')
		return (ft_putn_b((unsigned int)nbr, "0123456789abcdef", 1));
	if (c == 'X')
		return (ft_putn_b((unsigned int)nbr, "0123456789ABCDEF", 1));
	return (0);
}
