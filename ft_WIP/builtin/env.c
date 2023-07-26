/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:58:32 by flplace           #+#    #+#             */
/*   Updated: 2023/07/26 15:57:00 by flplace          ###   ########.fr       */
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
	int		stdout_copy;
	t_env	*parse;

	parse = NULL;
	stdout_copy = dup(STDOUT_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
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
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	return (0);
}
