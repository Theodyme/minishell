/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:54:46 by flplace           #+#    #+#             */
/*   Updated: 2023/03/15 15:57:06 by flplace          ###   ########.fr       */
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
	(void)cmd;
	return (1);
}