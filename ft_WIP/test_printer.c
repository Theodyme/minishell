/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:41:16 by flplace           #+#    #+#             */
/*   Updated: 2023/02/26 22:29:27 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_printer(t_env **envt)
{
	t_env	*parse;

	parse = (*envt);
	while (parse->next)
	{
		printf("key = '%s',\nvalue = '%s'\n\n", parse->key, parse->value);
		parse = parse->next;
	}
	return ;
}
