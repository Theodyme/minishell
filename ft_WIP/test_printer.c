/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:41:16 by flplace           #+#    #+#             */
/*   Updated: 2023/02/10 11:22:31 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_printer(t_env **envt)
{
	t_env	*parse;

	parse = (*envt);
	// printf("parse = %p, envt = %p\n", parse, envt);
	while (parse->next)
	{
		printf("envt printer:\nkey = '%s',\nvalue = '%s'\n", parse->key, parse->value);
		parse = parse->next;
	}
	return ;
}
