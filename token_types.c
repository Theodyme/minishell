/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:59:32 by mabimich          #+#    #+#             */
/*   Updated: 2023/08/14 16:40:07 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
