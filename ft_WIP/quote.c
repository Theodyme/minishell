/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:50:46 by mabimich          #+#    #+#             */
/*   Updated: 2023/08/14 16:27:35 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_quote(char *str)
{
	int		i;
	int		v;
	char	c;

	i = -1;
	v = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
				v++;
			else
				return (-1);
		}
	}
	return (v);
}

int	ft_quotelen(char *str)
{
	int		i;
	char	c;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
	{
		c = str[i++];
		while (str[i] && str[i] != c)
			i++;
		if (str[i] && str[i] == c)
			return (i + 1);
	}
	return (-1);
}
