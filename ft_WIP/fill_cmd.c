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
	if (!tmp->file)
		return (free(tmp), 1);
	return (0);
}

int	ft_redir(t_token *token, t_cmd *cmd)
{
	if (token->type != REDIR_IN && token->type != REDIR_OUT && token->type != APPEND)
		return (printf("Error3: unexpected token type: %d\n", token->type), 1);
	else if (token->next && token->next->type != WORD)
		return (printf("Error4: unexpected token type: %d\n", token->next->type), 1);
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
	tmp->str = ft_strdup(str);
	if (!tmp->str)
		return (free(tmp->next), 1);
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
	while (tkn && tkn->type != PIPE)
	{
		if (tkn->type == WORD)
		{
			if (!cmd->name)
			{
				cmd->name = ft_strdup(tkn->str);
				if (!cmd->name)
					return (1);
			}
			else
			{
				if (ft_create_arg(&(cmd->args_list)))
					return (printf("Error: ft_create_arg failed\n"), 1);
				else if (ft_add_arg(cmd->args_list, tkn->str))
					return (printf("Error: ft_add_arg failed\n"), 1);
			}
		}
		else if (!ft_redir(tkn, cmd))
			tkn = tkn->next;
		else
			return (1);
		tkn = tkn->next;
	}
	return (0);
}