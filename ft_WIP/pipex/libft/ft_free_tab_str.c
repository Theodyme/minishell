/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:50:25 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/05 18:54:09 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab_str(char **tab, int max)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	if (max != -1)
		while (i < max)
			free(tab[i++]);
	else
		while (tab[i])
			free(tab[i++]);
	free(tab);
}
