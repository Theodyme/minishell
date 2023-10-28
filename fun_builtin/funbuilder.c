/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funbuilder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:55:44 by flplace           #+#    #+#             */
/*   Updated: 2023/10/28 22:38:02 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_tolower(int n)
{
	if (n >= 'A' && n <= 'Z')
		n += 32;
	return (n);
}

char *ft_str_tolower(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

// int ft_fun_builder(t_cmd **cmd)
// {
// 	int i;
// 	const t_fn 

// 	i = 0;
// 	if (!(*cmd)->name)
// 	{
// 		if (!(*cmd)->redir || ((*cmd)->redir && !(*cmd)->redir->type))
// 			return (2);
// 		return (0);
// 	}
// 	while (bltin[i].call && ft_strcmp(bltin[i].call, ft_str_tolower((*cmd)->name)) != 0)
// 		i++;
// 	if (bltin[i].call)
// 		(*cmd)->bltn = tab_bltin[i].blt_fn;
// 	return (0);
// }
