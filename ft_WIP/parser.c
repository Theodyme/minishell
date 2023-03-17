#include "minishell.h"

int	ft_token_to_cmd(t_token *head, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
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
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == APPEND)
		{
			if (!tmp->next || tmp->next->type != WORD)
				return (printf("Error1: unexpected token type: %d\n", tmp->type), 1);
		}
		else if (tmp->type == PIPE)
		{
			if (!tmp->next || tmp->next->type == PIPE)
				return (printf("Error2: unexpected token type: %d\n", tmp->type), 1);
		}
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
		while (tmp && ++i)
			tmp = tmp->next;
		cmd->args = ft_calloc(i + 1, sizeof(char *));
		if (!cmd->args)
			return (1);
		tmp = cmd->args_list;
		i = 0;
		while (tmp && tmp->next)
		{
			cmd->args[i] = ft_strdup(tmp->str);
			if (!cmd->args[i])
				return (1);
			i++;
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

t_cmd	*ft_parser(t_token *token)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (ft_check_syntax(token))
		return (NULL);
	ft_token_to_cmd(token, cmd);
	ft_argslist_to_array(cmd);
	ft_print_cmd(cmd);
	return (cmd);
}
