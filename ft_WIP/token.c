/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:59:32 by mabimich          #+#    #+#             */
/*   Updated: 2023/08/13 21:52:03 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else
		printf("Error: ft_specialtoken\n");
	return (token);
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
	size_t	len;

	if (line[0] == '\'')
		token->type = QUOTE;
	else
		token->type = DQUOTE;
	len = ft_quotelen(line);
	token->str = ft_strndup(line + 1, len - 2);
	*i += len;
	return (token);
}

t_token	*ft_wordtoken(int *i, char *line, t_token *token)
{
	size_t	len;

	token->type = WORD;
	len = ft_wordlen(line);
	token->str = ft_strndup(line, len);
	*i += len;
	return (token);
}

t_token	*ft_blanktoken(int *i, char *line, t_token *token)
{
	token->type = BLANK;
	token->str = strdup(" ");
	*i += ft_spacelen(line);
	return (token);
}

void	ft_delimiter_set(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->next->type == WORD)
		{
			tmp->next->type = DELIMITER;
			printf("checking delimiter\n");
		}
		tmp = tmp->next;
	}
	return ;
}

t_token *ft_tokenize(const char *line)
{
	t_token	*head;
	t_token	*tmp;
	char	*newline;
	int		i;

	i = 0;
	head = ft_calloc(1, sizeof(t_token));
	if (!head)
		return (NULL);
	tmp = head;
	newline = ft_strtrim(line, C_BLANK);
	while (newline[i])
	{
		if (ft_isblank(newline[i]))
			tmp = ft_blanktoken(&i, newline + i, tmp);
		else if (newline[i] == '\'' || newline[i] == '\"')
			tmp = ft_quotetoken(&i, newline + i, tmp);
		else if (newline[i] && ft_isspecial(newline[i]))
			tmp = ft_specialtoken1(&i, newline + i, tmp);
		else
			tmp = ft_wordtoken(&i, newline + i, tmp);
		tmp->next = ft_calloc(1, sizeof(t_token));
		if (!tmp->next)
		{
			free(newline);
			return (ft_free_lst_token(head), NULL);
		}
		tmp = tmp->next;
	}
	tmp->type = EOL;
	tmp->str = ft_strdup("newline");
	free(newline);
	return (head);
}
