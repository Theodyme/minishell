/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:02:39 by mabimich          #+#    #+#             */
/*   Updated: 2022/05/31 19:07:53 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nblen_itoa(int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		i++;
	while (nb >= 10 || nb <= -10)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		nc;
	long	nb;

	nb = n;
	nc = ft_nblen_itoa(nb);
	r = (char *)ft_calloc((nc + 1), sizeof(*r));
	if (r == NULL)
		return (NULL);
	r[nc] = '\0';
	if (!nb)
		r[0] = '0';
	if (nb < 0)
	{
		r[0] = '-';
		nb *= -1;
	}
	while (nb)
	{
		r[--nc] = ((nb % 10) + '0');
		nb /= 10;
	}
	return (r);
}
