/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:07:52 by flplace           #+#    #+#             */
/*   Updated: 2023/05/26 16:08:32 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_bltin_exit(t_cmd *cmd)
//

//

int	ft_bltin_exit(t_cmd *cmd)
{
	printf("exit\n");
	// ft_clear_env(cmd->envt);
	// ft_free_cmd(cmd);
	// exit(0);
	ft_free_n_exit(cmd, 0);
	return (1);
}
