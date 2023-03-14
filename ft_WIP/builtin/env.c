/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:58:32 by flplace           #+#    #+#             */
/*   Updated: 2023/03/10 16:54:04 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bltin_env(t_cmd *div)
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
