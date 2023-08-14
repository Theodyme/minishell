/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:13:09 by theophane         #+#    #+#             */
/*   Updated: 2023/08/14 15:28:35 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
		write(STDOUT_FILENO, "\n", 1);
        rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
    }
    return ;
}

void    sig_init()
{
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    return ;
}

void    sig_heredoc(int signum)
{
    (void)signum;
    return ;
}
