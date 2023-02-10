
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:45:17 by flplace           #+#    #+#             */
/*   Updated: 2023/02/02 17:52:42 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
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

int	ft_trim_blank(char *line)
{
	int i;

	i = 0;
	while (line[i] && ft_isblank(line[i]))
		i += 1;
	return (i);
}

int	ft_wordlen(char *line)
{
	int i;

	i = 0;
	while (line[i] && !ft_isblank(line[i]) && !ft_isspecial(line[i])
		&& !ft_isquote(line[i]))
		i++;
	return (i);
}


int ft_wordlen_with_dollar(char *line)
{
	int i;

	i = 0;
	while (line[i] && !ft_isblank(line[i]) && !ft_isspecial(line[i])
		&& !ft_isquote(line[i]) && line[i] != '$')
		i++;
	return (i);
}

void	ft_free_lst(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

t_token *ft_quotetoken(char *line, t_token *token)
{
	token->type = QUOTE;
	token->str = ft_strndup(line, ft_quotelen(line));
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
		i += ft_trim_blank(line + i);
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (line[i] == '\'')
				tmp->type = QUOTE;
			else
				tmp->type = DQUOTE;
			tmp->str = ft_strndup(line + i + 1, ft_quotelen(line + i) - 2);
			i += ft_quotelen(line + i);

		}
		else if (line[i] && ft_isspecial(line[i]))
			tmp = ft_specialtoken1(&i, line + i, tmp);
		else
		{
			tmp->type = WORD;
			tmp->str = ft_strndup(line + i, ft_wordlen(line + i));
			i += ft_wordlen(line + i);
		}
		tmp->next = ft_calloc(1, sizeof(t_token));
		if (!tmp->next)
			return (ft_free_lst(head), NULL);
		tmp = tmp->next;
	}
	return (head);
}

void	ft_print_token(t_token *head)
{
	t_token *tmp;

	tmp = head;
	while (tmp)
	{
		printf("type: %d, str: %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
}

void	ft_print_env(t_env *head)
{
	t_env *tmp;

	tmp = head;
	while (tmp->next)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
/*
void	ft_testmodif(t_token *head)
{
	t_token *tmp;

	tmp = head;
	while (tmp->next)
	{
		if (tmp->type == WORD)
		{
			free(tmp->str);
			tmp->str = ft_strdup("test");
		}
		tmp = tmp->next;
	}
}*/


int main(int ac, char **av, char **env)
{
	char	*line = NULL;
	t_env	*l_env;
	t_token *head;
	
	if (ac != 1 && av)
		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
	
	//ft_print_env(l_env);
	while (true)
	{
		line = readline(ft_strdup("$> "));
		if (!line)
			break ;
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		if (ft_count_quote(line) != -1)
		{
			head = ft_tokenize(line);
			if (!head)
				return (write(2, "Error: Tokenization failed\n", 27), 1);
		//	ft_testmodif(head);
			ft_print_token(head);
			ft_expand(head, l_env);
			//ft_quote(line, head);
		}
		else
			write(2, "Error: Unmatched quote\n", 23);
		ft_add_history(line);
		write(1, "\n", 1);
	}
	return (0);
}
