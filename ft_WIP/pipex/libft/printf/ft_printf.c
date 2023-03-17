/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:14:47 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/15 20:54:14 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *par, ...)
{
	va_list	pars;
	size_t	l;
	size_t	i;

	l = 0;
	i = 0;
	va_start(pars, par);
	while (i + ft_strclen((char *)&par[i], '%') <= ft_strlen(par))
	{
		l += ft_putcstr((char *)&par[i], '%');
		i += ft_strclen((char *)&par[i], '%');
		if (i++ >= ft_strlen(par))
			break ;
		if (par[i] == 's')
			l += ft_putstr(va_arg(pars, char *));
		if (par[i] == 'c')
			l += ft_putchar(va_arg(pars, int));
		if (par[i] == '%')
			l += write(1, "%", 1);
		if (par[i] == 'p' || par[i] == 'x' || par[i] == 'X' || par[i] == 'u'
			|| par[i] == 'd' || par[i] == 'i')
			l += ft_dispatch_nb(va_arg(pars, unsigned long), par[i]);
		i++;
	}
	return (va_end(pars), l);
}
