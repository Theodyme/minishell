/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:54:46 by flplace           #+#    #+#             */
/*   Updated: 2023/04/03 14:57:46 by mabimich         ###   ########.fr       */
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
	int		out;

	out = STDOUT_FILENO;
	if (cmd->next)
		out = cmd->next->fd[1];
	ft_putendl_fd(cmd->argv[1], out);
	return (0);
}
