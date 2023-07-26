/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:41:16 by flplace           #+#    #+#             */
/*   Updated: 2023/07/26 16:23:37 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_pwd(t_cmd *cmd)
{
	int		stdout_copy;
	t_env	*pwd;

	stdout_copy = dup(STDOUT_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	pwd = NULL;
	pwd = ft_key_finder(&(cmd->envt), "PWD");
	if (pwd == NULL)
		return (1);
	ft_putendl_fd(pwd->value, 1);
	ft_putendl_fd("\n", 1);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	return (0);
}
