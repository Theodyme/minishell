/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:43:10 by flplace           #+#    #+#             */
/*   Updated: 2023/02/08 19:15:39 by flplace          ###   ########.fr       */
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

size_t    ft_strclen(char *str, char c)
{
    size_t    i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}
