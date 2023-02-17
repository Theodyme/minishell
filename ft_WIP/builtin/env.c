/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:58:32 by flplace           #+#    #+#             */
/*   Updated: 2023/02/17 17:27:06 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bltin_env(t_env **envt)
{
	t_env	*parse;

	if (!(*envt))
	{
		printf("env error: nothing to print.\n");
		return ;
	}
	parse = (*envt);
	while (parse->next)
	{
		printf("%s=%s\n", parse->key, parse->value);
		parse = parse->next;
	}
	printf("%s=%s\n", parse->key, parse->value);
	return ;
}
