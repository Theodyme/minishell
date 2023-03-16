/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:07:52 by flplace           #+#    #+#             */
/*   Updated: 2023/03/15 16:59:33 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_bltin_exit(t_cmd *cmd)
//

//

int	ft_bltin_exit(t_cmd *cmd)
{
	ft_clear_env(cmd->envt);
	return (1);
}
