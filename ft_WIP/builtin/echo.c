/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:54:46 by flplace           #+#    #+#             */
/*   Updated: 2023/02/24 12:10:20 by flplace          ###   ########.fr       */
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

void	ft_bltin_echo(char *echo, int flag, int fdout)
{


}
