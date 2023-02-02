/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:52:16 by flplace           #+#    #+#             */
/*   Updated: 2023/02/02 13:52:33 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *src)
{
	int		l;
	char	*str;

	if (src == NULL)
		return (NULL);
	l = ft_strlen((char *)src);
	str = (char *)ft_calloc(sizeof(*str), (l + 1));
	if (str == NULL)
		return (NULL);
	str = ft_strcpy(str, src);
	return (str);
}
