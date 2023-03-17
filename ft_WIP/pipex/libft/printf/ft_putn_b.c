/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putn_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:39:34 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/15 20:41:00 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putn_b(unsigned long long nbr, char *base, size_t i)
{
	unsigned long long	snbr;

	snbr = ft_strlen(base);
	if (nbr >= snbr)
		i = ft_putn_b(nbr / snbr, base, ++i);
	nbr = base[nbr % snbr];
	write(1, &nbr, 1);
	return (i);
}
