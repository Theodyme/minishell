/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:24:45 by manuel            #+#    #+#             */
/*   Updated: 2022/08/07 19:20:39 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_create_fname(char *fname)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*base_name;

	i = -1;
	if (fname && access(fname, F_OK))
		return (ft_strdup(fname));
	else
		base_name = ft_strjoin(fname, "_");
	while (++i >= 0 && fname && !(access(fname, F_OK)))
	{
		tmp = ft_itoa(i);
		if (i > 0)
			tmp2 = fname;
		fname = ft_strjoin(base_name, tmp);
		if (!fname)
			return (NULL);
		free(tmp);
		free(tmp2);
	}
	free(base_name);
	return (fname);
}
