#include "minishell.h"

int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_isspecial(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_trim_blank(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isblank(line[i]))
		i += 1;
	return (i);
}

t_token	*ft_specialtoken1(int *i, char *line, t_token *token)
{
	*i += 1;
	if (line[0] == '|')
	{
		token->type = PIPE;
		token->str = ft_strdup("|");
	}
	else if (line[0] == '>' && line[1] && line[1] == '>')
	{
		token->type = APPEND;
		token->str = ft_strdup(">>");
		*i += 1;
	}
	else if (line[0] == '>')
	{
		token->type = REDIR_OUT;
		token->str = ft_strdup(">");
	}
	else
		token = ft_specialtoken2(i, line, token);
	return (token);
}

t_token	*ft_specialtoken2(int *i, char *line, t_token *token)
{
	if (line[0] == '<' && line[1] && line[1] == '<')
	{
		token->type = HEREDOC;
		token->str = ft_strdup("<<");
		*i += 1;
	}
	else if (line[0] == '<')
	{
		token->type = REDIR_IN;
		token->str = ft_strdup("<");
	}
	return (token);
}

int	ft_wordlen(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isblank(line[i]) && !ft_isspecial(line[i])
		&& !ft_isquote(line[i]))
		i++;
	return (i);
}

int	ft_spacelen(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isblank(line[i]))
		i++;
	return (i);
}

void	ft_free_lst_token(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

t_token	*ft_quotetoken(int *i, char *line, t_token *token)
{
	if (line[0] == '\'')
		token->type = QUOTE;
	else
		token->type = DQUOTE;
	token->str = ft_strndup(line + 1, ft_quotelen(line) - 2);
	*i += ft_quotelen(line);
	return (token);
}

t_token	*ft_wordtoken(int *i, char *line, t_token *token)
{
	token->type = WORD;
	token->str = ft_strndup(line, ft_wordlen(line));
	*i += ft_wordlen(line);
	return (token);
}

t_token	*ft_blanktoken(int *i, char *line, t_token *token)
{
	token->type = BLANK;
	token->str = strdup(" ");
	*i += ft_spacelen(line);
	return (token);
}

t_token	*ft_tokenize(char *line)
{
	t_token	*head;
	t_token	*tmp;
	int		i;

	i = 0;
	head = ft_calloc(1, sizeof(t_token));
	if (!head)
		return (NULL);
	tmp = head;
	while (line[i])
	{
		if (ft_isblank(line[i]))
			tmp = ft_blanktoken(&i, line + i, tmp);
		else if (line[i] == '\'' || line[i] == '\"')
			tmp = ft_quotetoken(&i, line + i, tmp);
		else if (line[i] && ft_isspecial(line[i]))
			tmp = ft_specialtoken1(&i, line + i, tmp);
		else
			tmp = ft_wordtoken(&i, line + i, tmp);
		tmp->next = ft_calloc(1, sizeof(t_token));
		if (!tmp->next)
			return (ft_free_lst_token(head), NULL);
		tmp = tmp->next;
	}
	return (head);
}

void	ft_print_token(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("type: %d, str: |%s|\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
}

void	ft_print_env(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp->next)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
