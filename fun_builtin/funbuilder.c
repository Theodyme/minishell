/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funbuilder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:55:44 by flplace           #+#    #+#             */
/*   Updated: 2023/10/30 22:01:34 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tolower(int n)
{
	if (n >= 'A' && n <= 'Z')
		n += 32;
	return (n);
}

char	*ft_str_tolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}
