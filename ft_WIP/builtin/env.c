/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:58:32 by flplace           #+#    #+#             */
/*   Updated: 2023/09/04 19:16:53 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_keynvalue(t_env *parse)
{
	ft_putendl_fd(parse->key, 1);
	ft_putendl_fd("=", 1);
	ft_putendl_fd(parse->value, 1);
	ft_putendl_fd("\n", 1);
	return ;
}

int	ft_bltin_env(t_cmd *cmd)
{
	t_env	*parse;

	parse = NULL;
	parse = cmd->envt;
	if (parse == NULL)
	{
		printf("env error: nothing to print.\n");
		return (1);
	}
	while (parse->next)
	{
		ft_print_keynvalue(parse);
		parse = parse->next;
	}
	if (parse)
		ft_print_keynvalue(parse);
	return (0);
}
