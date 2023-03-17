/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:04:43 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/07 17:49:12 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	size_t		r;
	int			m;

	i = 0;
	r = 0;
	m = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			m = -1;
	while (ft_isdigit((int)str[i]))
	{
		if ((r * 10) + sizeof(char) > LONG_MAX)
		{
			if (m > 0)
				return (-1);
			else
				return (0);
		}
		r = r * 10 + str[i++] - '0';
	}
	return (m * r);
}
