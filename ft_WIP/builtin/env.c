/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:58:32 by flplace           #+#    #+#             */
/*   Updated: 2023/03/03 12:48:49 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_env(t_cmd_div *div)
{
	t_env	*parse = NULL;

	// printf("node %p, %s=%s, next %p\n", div->envt, div->envt->key, div->envt->value, div->envt->next);
	parse = div->envt;
	if (parse == NULL)
	{
		printf("env error: nothing to print.\n");
		return ;
	}
	while (parse->next)
	{
		printf("%s=%s\n", parse->key, parse->value);
		parse = parse->next;
	}
	printf("%s=%s\n", parse->key, parse->value);
	return ;
}
