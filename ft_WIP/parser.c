#include "minishell.h"

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		printf("array[%d]: %s\n", i, array[i]);
		i++;
	}
}

void	ft_print_cmd(t_cmd *cmd)
{
	t_cmd	*start;
	t_arg	*tmp;
	t_redir	*tmp2;

	start = cmd;
	printf("_____PRINTING CMD______\n");
	while (cmd)
	{
		printf("name: %s\n", cmd->name);
		tmp = cmd->args_list;
		while (tmp)
		{
			printf("arg: %s\n", tmp->str);
			tmp = tmp->next;
		}
		tmp2 = cmd->redir;
		while (tmp2)
		{
			printf("redirect type: %d --> file: %s\n", tmp2->type, tmp2->file);
			tmp2 = tmp2->next;
		}
		ft_print_array(cmd->args);
		cmd = cmd->next;
		printf("_______________________\n");
	}
	cmd = start;
}

int	ft_add_redir(t_redir *redir, t_token *token)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_calloc(1, sizeof(t_redir));
	if (!tmp->next)
		return (1);
	tmp->type = token->type;
	tmp->file = ft_strdup(token->next->str);
	printf("file: %s\n", tmp->file);
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

int	ft_fill_cmd(t_cmd *cmd, t_token *tkn)
{
	while (tkn && tkn->type != PIPE)
	{
		printf("inside fill_cmd; for token = %s\n", tkn->str);
		if (tkn->type == WORD && !cmd->name)
		{
			cmd->name = ft_strdup(tkn->str);
			if (!cmd->name)
				return (1);
		}
		else if (tkn->type == WORD && cmd->name)
		{
			if (!cmd->args_list)
			{
				cmd->args_list = ft_calloc(1, sizeof(t_arg));
				if (!cmd->args_list)
					return (1);
			}
			if (ft_add_arg(cmd->args_list, tkn->str))
				return (printf("Error: ft_add_arg failed\n"), 1);
		}
		else if (!ft_redir(tkn, cmd))
			tkn = tkn->next;
		else
			return (1);
		tkn = tkn->next;
	}
	return (0);
}

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
			if (!tmp->next && tmp->next->type == PIPE)
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
		while (tmp && i++)
			tmp = tmp->next;
		cmd->args = ft_calloc(i + 1, sizeof(char *));
		if (!cmd->args)
			return (1);
		// cmd->args[0] = ft_strdup(cmd->name);
		// if (!cmd->args[0])
		// 	return (1);
		tmp = cmd->args_list;
		i = 0;
		while (tmp)
		{
			// cmd->args[i] = ft_strdup(tmp->str);
			ft_strcpy(tmp->str, cmd->args[i]);
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
	t_cmd	*cmd = NULL;

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
