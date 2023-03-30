/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:29:26 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/30 17:29:27 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_tab(char **tab)
{
	char	*str;
	char	*tofree;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (tab[i])
	{
		tofree = str;
		str = ft_strjoin(str, tab[i]);
		free(tofree);
		free(tab[i]);
		i++;
	}
	free(tab);
	return (str);
}
