/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:59:32 by mabimich          #+#    #+#             */
/*   Updated: 2023/08/14 16:18:25 by flplace          ###   ########.fr       */
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

int	ft_token_attribution(char *newline, int *i, t_token **tmp)
{
	while (newline[*i])
	{
		if (ft_isblank(newline[*i]))
			*tmp = ft_blanktoken(i, newline + *i, *tmp);
		else if (newline[*i] == '\'' || newline[*i] == '\"')
			*tmp = ft_quotetoken(i, newline + *i, *tmp);
		else if (newline[*i] && ft_isspecial(newline[*i]))
			*tmp = ft_specialtoken1(i, newline + *i, *tmp);
		else
			*tmp = ft_wordtoken(i, newline + *i, *tmp);
		(*tmp)->next = ft_calloc(1, sizeof(t_token));
		if (!(*tmp)->next)
		{
			free(newline);
			return (1);
		}
		*tmp = (*tmp)->next;
	}
	return (0);
}

t_token	*ft_tokenize(const char *line)
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
	if (ft_token_attribution(newline, &i, &tmp) == 1)
		return (ft_free_lst_token(head), NULL);
	tmp->type = EOL;
	tmp->str = ft_strdup("newline");
	free(newline);
	return (head);
}
