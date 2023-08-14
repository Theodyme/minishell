/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:13:09 by theophane         #+#    #+#             */
/*   Updated: 2023/08/14 19:34:35 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
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

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		g_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd(TRITON, 2);
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_status = 131;
	}
}

void	sig_init(int state)
{
	if (state)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (!state)
	{
		signal(SIGINT, sig_handler_child);
		signal(SIGQUIT, sig_handler_child);
	}
	return ;
}

void	sig_heredoc(int signum)
{
	(void)signum;
	return ;
}
