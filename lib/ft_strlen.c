/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:43:10 by flplace           #+#    #+#             */
/*   Updated: 2023/10/24 21:01:55 by mabimich         ###   ########.fr       */
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

size_t	ft_strclen(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

size_t	ft_strsetlen(const char *str, char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (str == NULL || set == NULL)
		return (0);
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

size_t	ft_strnosetlen(const char *str, char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (str == NULL || set == NULL)
		return (0);
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				break ;
			j++;
		}
		if (!set[j])
			return (i);
		i++;
	}
	return (i);
}
