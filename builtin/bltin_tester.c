/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:12 by flplace           #+#    #+#             */
/*   Updated: 2023/10/24 18:47:13 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_exec(t_cmd **cmd, const t_fn bltin[12], int i)
{
	int			stdout_copy;

	if ((*cmd)->name && bltin[i].call)
	{
		if (ft_strcmp(bltin[i].call, "exit") == 0)
		{
			(*cmd)->status = bltin[i].blt_fn(*cmd);
			return (1);
		}
		open_files(*cmd);
		stdout_copy = dup(STDOUT_FILENO);
		dup2((*cmd)->fd[1], STDOUT_FILENO);
		(g_status) = bltin[i].blt_fn(*cmd);
		(*cmd)->status = g_status;
		close((*cmd)->fd[1]);
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
		return (1);
	}
	return (0);
}

int	ft_bltin_tester(t_cmd **cmd)
{
	int			i;
	const t_fn	bltin[12] = {
	{.call = "echo", .blt_fn = &ft_bltin_echo},
	{.call = "cd", .blt_fn = &ft_bltin_cd},
	{.call = "pwd", .blt_fn = &ft_bltin_pwd},
	{.call = "export", .blt_fn = &ft_bltin_export},
	{.call = "unset", .blt_fn = &ft_bltin_unset},
	{.call = "env", .blt_fn = &ft_bltin_env},
	{.call = "exit", .blt_fn = &ft_bltin_exit},
	};

	i = 0;
	if (!(*cmd)->name)
	{
		if (!(*cmd)->redir->type)
			return (2);
		return (0);
	}
	while (bltin[i].call && ft_strcmp(bltin[i].call, (*cmd)->name) != 0)
		i++;
	(*cmd)->pid = 1;
	return (ft_bltin_exec(cmd, bltin, i));
}
