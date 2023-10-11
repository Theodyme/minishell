/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_gets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:09:18 by mabimich          #+#    #+#             */
/*   Updated: 2023/07/26 16:09:19 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_history(char *line)
{
	if (line && *line)
		add_history(line);
	if (line)
	{
		free(line);
		line = NULL;
	}
	return ;
}

int	in_quote(char **ptr1, char **ptr2)
{
	if (ptr1 == NULL || ptr2 == NULL || **ptr1 == '\0' || **ptr2 == '\0')
		return (0);
	*ptr2 = *ptr2 + 1;
	if (**ptr1 != '\'' && **ptr1 != '\"')
	{
		*ptr1 = *ptr1 + 1;
		return (0);
	}
	else
	{
		if (**ptr1 == **ptr2)
			return (*ptr1 = ++(*ptr2), 0);
		else if (**ptr1 == '\'')
			return (1);
		else if (**ptr1 == '\"')
			return (2);
	}
	return (0);
}
