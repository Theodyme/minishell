/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:59 by flplace           #+#    #+#             */
/*   Updated: 2023/10/23 15:54:50 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_prev_finder(char *needle, t_env **envt)
{
	t_env	*parse;

	parse = (*envt);
	while (parse->next)
	{
		if (ft_strcmp(parse->next->key, needle) == 0)
			break ;
		parse = parse->next;
	}
	if (ft_strcmp(parse->key, needle) != 0 && parse->next == NULL)
		return (NULL);
	return (parse);
}

int	ft_unset_needle(char *needle, t_cmd *cmd)
{
	t_env	*prev;
	t_env	*torm;

	if (ft_strcmp((*cmd->envt)->key, needle) == 0)
	{
		torm = *(cmd->envt);
		*(cmd->envt) = (*cmd->envt)->next;
	}
	else
	{
		prev = ft_prev_finder(needle, cmd->envt);
		if (!prev)
			return (0);
		torm = prev->next;
		prev->next = torm->next;
	}
	ft_key_remove(torm);
	return (0);
}

int	ft_bltin_unset(t_cmd *cmd)
{
	t_arg	*args;
	t_env	*env;

	env = *(cmd->envt);
	if (!(env->key))
		return (1);
	args = cmd->args_list->next;
	while (args && args->str)
	{
		if (ft_unset_needle(args->str, cmd) == 1)
			return (1);
		args = args->next;
	}
	return (0);
}
