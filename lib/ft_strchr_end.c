/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:55:58 by mabimich          #+#    #+#             */
/*   Updated: 2023/06/28 10:03:23 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr_end(const char *s, int c)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = ft_strlen(s) + 1;
	while (s[--i] != (char)c)
		if (i == 0)
			return (-1);
	return (i);
}
