/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:37:09 by theophane         #+#    #+#             */
/*   Updated: 2023/08/04 14:37:28 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
