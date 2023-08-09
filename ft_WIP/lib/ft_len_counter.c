/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:46:27 by theophane         #+#    #+#             */
/*   Updated: 2023/08/07 15:01:07 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_wordlen(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isblank(line[i]) && !ft_isspecial(line[i]) && !ft_isquote(line[i]))
		i++;
	return (i);
}

int	ft_spacelen(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isblank(line[i]))
		i++;
	return (i);
}
