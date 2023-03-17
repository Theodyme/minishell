/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:21:44 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/10 23:48:11 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// la fonction free_tab permet de free un tableau de str dans lequel une des
// assignations a été fail par un malloc.
// Il saute donc au dessus de cet élément
// Il ne faut donc pas envoyer de tableau bien assigné.
// Si str existe, il le free aussi

void	free_tab_with_1blank(char **tab, char *str)
{
	size_t	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
	if (str)
		free(str);
}
