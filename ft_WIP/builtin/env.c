/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:58:32 by flplace           #+#    #+#             */
/*   Updated: 2023/02/23 17:07:46 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bltin_env(t_cmd_div *div)
{
	t_env	*parse;

	if (!(div->envt))
	{
		printf("env error: nothing to print.\n");
		return ;
	}
	parse = div->envt;
	while (parse->next)
	{
		printf("%s=%s\n", parse->key, parse->value);
		parse = parse->next;
	}
	printf("%s=%s\n", parse->key, parse->value);
	return ;
}
