/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:12 by flplace           #+#    #+#             */
/*   Updated: 2023/10/29 23:46:32 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_bltin_exec(t_cmd **cmd)
{
	int	i;

	i = -1;
	if (!(*cmd)->name)
		dispatch_exit((*cmd), 21);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_DFL);
	i = (*cmd)->bltn(*cmd);
	if ((*cmd) && (*cmd)->head->next)
		dispatch_exit((*cmd), i);
	return (i);
}

static const t_fn	*call_tab_bltin(void)
{
	static const t_fn	tab_bltin[11] = {
	{.call = "echo", .blt_fn = &ft_bltin_echo},
	{.call = "cd", .blt_fn = &ft_bltin_cd},
	{.call = "pwd", .blt_fn = &ft_bltin_pwd},
	{.call = "export", .blt_fn = &ft_bltin_export},
	{.call = "unset", .blt_fn = &ft_bltin_unset},
	{.call = "env", .blt_fn = &ft_bltin_env},
	{.call = "exit", .blt_fn = &ft_bltin_exit},
	{.call = "hello", .blt_fn = &ft_bltin_hello},
	{.call = "hi", .blt_fn = &ft_bltin_hello},
	{.call = "where", .blt_fn = &ft_bltin_where},
	{0, 0}
	};

	return (tab_bltin);
}

t_bltin	ft_bltin_tester(t_cmd **cmd)
{
	int			i;
	const t_fn	*tab_bltin;

	tab_bltin = call_tab_bltin();
	i = 0;
	if (!(*cmd)->name) // ?
	{
		if (!(*cmd)->redir || ((*cmd)->redir && !(*cmd)->redir->type))
			return (0);
	}
	while (tab_bltin[i].call && ft_strcmp(tab_bltin[i].call, (*cmd)->name) != 0 \
		&& i <= 6)
		i++;
	while (tab_bltin[i].call && ft_strcmp(tab_bltin[i].call, (*cmd)->name) != 0)
		i++;
	(*cmd)->bltn = tab_bltin[i].blt_fn;
	return (0);
}
