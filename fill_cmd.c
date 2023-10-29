/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:54:00 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/29 16:09:16 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_redir(t_redir *redir, t_token *token)
{
	t_redir	*tmp;

	tmp = redir;
	if (tmp->file)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_calloc(1, sizeof(t_redir));
		if (!tmp->next)
			return (1);
		tmp = tmp->next;
	}
	tmp->type = token->type;
	tmp->file = ft_strdup(token->next->str);
	if (tmp->type == HEREDOC)
		init_heredoc(tmp);
	if (!tmp->file)
		return (free(tmp), 1);
	return (0);
}

int	ft_redir(t_token *token, t_cmd *cmd)
{
	if (token->type != REDIR_IN && token->type != REDIR_OUT
		&& token->type != APPEND && token->type != HEREDOC)
		return (1);
	else if (!token->next)
		return (1);
	else if (token->next->type != WORD)
		return (1);
	if (!cmd->redir)
	{
		cmd->redir = ft_calloc(1, sizeof(t_redir));
		if (!cmd->redir)
			return (1);
	}
	if (ft_add_redir(cmd->redir, token))
		return (1);
	return (0);
}

int	ft_add_arg(t_arg *arg, char *str)
{
	t_arg	*tmp;

	tmp = arg;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_calloc(1, sizeof(t_arg));
	if (!tmp->next)
		return (1);
	tmp->next->str = ft_strdup(str);
	if (!tmp->next->str)
	{
		free(tmp->next);
		tmp->next = NULL;
		return (1);
	}
	return (0);
}

int	ft_create_arg(t_arg **arg)
{
	if (!(*arg))
		*arg = ft_calloc(1, sizeof(t_arg));
	if (!(*arg))
		return (1);
	return (0);
}

int	ft_fill_cmd(t_cmd *cmd, t_token *tkn)
{
	while (tkn && tkn->type != PIPE && tkn->type != EOL)
	{
		cmd->pid = 1;
		if (tkn->type == WORD && !cmd->name)
		{
			cmd->name = ft_strdup(tkn->str);
			if (!cmd->name)
				return (printf("Error: couldn't add command name\n"), 1);
			cmd->args_list = ft_calloc(1, sizeof(t_arg));
			if (!cmd->args_list)
				return (printf("Error: ft_create_arg failed\n"), 1);
			else if (ft_add_arg(cmd->args_list, tkn->str))
				return (printf("Error: ft_add_arg failed\n"), 1);
			ft_bltin_tester(&cmd);
		}
		else if (tkn->type == WORD && ft_add_arg(cmd->args_list, tkn->str))
			return (printf("Error: ft_add_arg failed\n"), 1);
		else if (!ft_redir(tkn, cmd))
			tkn = tkn->next;
		else if (tkn->type == EOL)
			return (1);
		tkn = tkn->next;
	}
	return (0);
}
