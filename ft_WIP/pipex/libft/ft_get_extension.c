/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_extension.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 00:13:17 by mabimich          #+#    #+#             */
/*   Updated: 2022/06/02 18:43:48 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_extension(char *name_file)
{
	int		i;

	i = ft_strlen(name_file) - 1;
	while (i && name_file[i] && name_file[i] != '.')
		i--;
	if (name_file[i + 1])
		return (name_file + i + 1);
	return (NULL);
}
