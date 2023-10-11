/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:55:58 by mabimich          #+#    #+#             */
/*   Updated: 2023/06/28 10:03:20 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	if (s == NULL)
		return (NULL);
	while (s[++i] != (char)c)
		if (s[i] == '\0')
			return (NULL);
	return ((char *)&(s[i]));
}