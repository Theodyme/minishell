/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:54:46 by flplace           #+#    #+#             */
/*   Updated: 2023/05/04 13:54:19 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* -------------- void	ft_bltin_echo(t_env **envt, char *echo) -------------- */
//
//			NEEDS TO PRINT IN THE RIGHT FD !
// 			Also: if -n, musn't add a newline at the end of the printed string,
//			so chek the flag.
//
// 			May need env variable if you're printing one ??

int			ft_bltin_echo(t_cmd *cmd)
{
	int stdout_copy;
	struct s_arg	*tmp;

	stdout_copy = dup(STDOUT_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	tmp = cmd->args_list->next;
	while (cmd->args_list && tmp)
	{
		ft_putendl_fd(tmp->str, 1);
		printf("should print : %s\n", tmp->str);
		tmp = tmp->next;
		printf("should print next : %s\n", tmp->str);
	}
	printf("getting out\n");
	dup2(stdout_copy, STDOUT_FILENO);
    close(stdout_copy);
	return (1);
}
