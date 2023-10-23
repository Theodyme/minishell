/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:23:49 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/23 14:27:04 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_token_to_cmd(t_token *head, t_cmd *cmd, t_env **envt)
{
	t_token	*tmp;
	t_cmd	*head_cmd;

	tmp = head;
	head_cmd = cmd;
	while (tmp)
	{
		while (tmp && tmp->type == WORD && !(*tmp->str))
			tmp = tmp->next;
		cmd->envt = envt;
		cmd->head = head_cmd;
		cmd->status = -1;
		ft_fill_cmd(cmd, tmp);
		while (tmp->next && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp->type == PIPE)
		{
			cmd->next = ft_calloc(1, sizeof(t_cmd));
			if (!cmd->next)
				return (1);
			cmd = cmd->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!tmp)
		return (printf(TRITON "syntax error\n"), 1);
	if (tmp->type == PIPE)
		return (printf(TRITON UNEXPECTED_TOKEN_ERR, tmp->str), 1);
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || \
		tmp->type == APPEND || tmp->type == HEREDOC)
		{
			if (!tmp->next || (tmp->next->type != WORD
					&& tmp->next->type != DELIMITER))
				return (printf(TRITON UNEXPECTED_TOKEN_ERR, tmp->next->str), 1);
		}
		else if (tmp->type == PIPE)
			if (!tmp->next || tmp->next->type == PIPE)
				return (printf(TRITON UNEXPECTED_TOKEN_ERR, tmp->str), 1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_argslist_to_array(t_cmd *cmd)
{
	t_arg	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->args_list;
		i = 0;
		while (tmp && tmp->next && ++i)
			tmp = tmp->next;
		cmd->argv = ft_calloc(i + 1, sizeof(char *));
		if (!cmd->argv)
			return (1);
		tmp = cmd->args_list;
		i = 0;
		while (tmp && tmp->str)
		{
			cmd->argv[i] = ft_strdup(tmp->str);
			if (!cmd->argv[i])
				return (1);
			i++;
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	ft_envlist_to_array(t_cmd *cmd)
{
	t_env	*tmp;
	int		i;

	tmp = *cmd->envt;
	i = 0;
	while (tmp && ++i)
		tmp = tmp->next;
	cmd->envp = ft_calloc(i + 1, sizeof(char *));
	if (!cmd->envp)
		return (1);
	tmp = *cmd->envt;
	i = 0;
	while (tmp)
	{
		cmd->envp[i] = ft_3strjoin_with_free(tmp->key, "=", tmp->value, 0);
		if (!cmd->envp[i])
			return (1);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

t_cmd	*ft_parser(t_token *token, t_env **envt)
{
	t_cmd	*cmd;

	if (ft_check_syntax(token))
		return (g_status = 2, NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_token_to_cmd(token, cmd, envt);
	ft_argslist_to_array(cmd);
	return (cmd);
}
