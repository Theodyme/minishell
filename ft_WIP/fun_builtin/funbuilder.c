/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funbuilder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:55:44 by flplace           #+#    #+#             */
/*   Updated: 2023/08/04 14:35:50 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tolower(int n)
{
	if (n >= 'A' && n <= 'Z')
		n += 32;
	return (n);
}

char	*ft_str_tolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int	ft_fun_builder(t_cmd **cmd)
{
	int			i;
	const t_fn	bltin[4] = {
	{.call = "hello", .blt_fn = &ft_bltin_hello},
	{.call = "hi", .blt_fn = &ft_bltin_hello},
	{.call = "where", .blt_fn = &ft_bltin_where},
	};

	i = 0;
	if (!(*cmd)->name)
		return (2);
	open_files(*cmd);
	while (bltin[i].call
		&& ft_strcmp(bltin[i].call, ft_str_tolower((*cmd)->name)) != 0)
		i++;
	(*cmd)->pid = 1;
	if (ft_strcmp((*cmd)->name, "exit") == 0)
		return (2);
	if (bltin[i].call)
	{
		(*cmd)->status = bltin[i].blt_fn(*cmd);
		return (1);
	}
	return (0);
}
