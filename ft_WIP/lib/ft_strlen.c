/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:43:10 by flplace           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/09 19:23:46 by mabimich         ###   ########.fr       */
=======
/*   Updated: 2023/02/08 19:15:39 by flplace          ###   ########.fr       */
>>>>>>> origin
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	int	l;

	l = 0;
	while (str && str[l] != '\0')
		l++;
	return (l);
}
<<<<<<< HEAD
size_t	ft_strclen(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
=======

size_t    ft_strclen(char *str, char c)
{
    size_t    i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}
>>>>>>> origin
