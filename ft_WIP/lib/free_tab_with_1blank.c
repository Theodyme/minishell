/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab_with_1blank.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:28:56 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/30 17:29:00 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab_with_1blank(char **tab)
{
	size_t	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
}
