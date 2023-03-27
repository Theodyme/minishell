#include "minishell.h"

int	ft_token_to_cmd(t_token *head, t_cmd *cmd, t_env *envt)
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
		return (printf("bash: syntax error\n"), 1);
	if (tmp->type == PIPE)
		return (printf("bash: syntax error near unexpected token `%s'\n", tmp->str), 1);
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == APPEND)
		{
			if (!tmp->next || tmp->next->type != WORD)
				return (printf("bash: syntax error near unexpected token `%s'\n", tmp->next->str), 1);
		}
		else if (tmp->type == PIPE)
		{
			if (!tmp->next || tmp->next->type == PIPE)
				return (printf("bash: syntax error near unexpected token `%s'\n", tmp->str), 1);
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

int ft_envlist_to_array(t_cmd *cmd)
{
	t_env	*tmp;
	int		i;

	//printf("CHECK envt: %s\n", cmd->envt->key);
	tmp = cmd->envt;
	i = 0;
	while (tmp && ++i)
		tmp = tmp->next;
	cmd->envp = ft_calloc(i + 1, sizeof(char *));
	if (!cmd->envp)
		return (1);
	tmp = cmd->envt;
	i = 0;
	while (tmp)
	{
		cmd->envp[i] = ft_3strjoin_with_free(tmp->key, "=", tmp->value, 0);
		if (!cmd->envp[i])
			return (1);
		i++;
		tmp = tmp->next;
	}
	//printf("print envp in envlist_to_array\n cmd->name %s ;cmd->envp[1]= %s\n", cmd->name, cmd->envp[1]);
	return (0);
}

void ft_print_linked_list(t_env *head)
{//inutile?
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("key: %s\n", tmp->key);
		printf("value: %s\n", tmp->value);
		tmp = tmp->next;
	}
}

t_cmd	*ft_parser(t_token *token, t_env *envt)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (ft_check_syntax(token))
		return (NULL);
	ft_token_to_cmd(token, cmd, envt);
	ft_argslist_to_array(cmd);
	
	// printf("print envt\n");
	// ft_print_linked_list(cmd->envt);
	// printf("print envp\n");
	// ft_print_array(cmd->envp);
	//ft_print_cmd(cmd);
	return (cmd);
}
