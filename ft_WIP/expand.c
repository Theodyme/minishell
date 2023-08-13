/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:34:12 by mabimich          #+#    #+#             */
/*   Updated: 2023/08/13 22:07:12 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_dollar(t_token *tkn, t_env *env)
{
	char	**tab;
	char	*tmp_str;
	size_t	i;
	size_t	j;

	i = ft_count_part(tkn->str);
	j = 0;
	tab = ft_calloc(i + 1, sizeof(char *));
	tmp_str = tkn->str;
	tab[j] = ft_strtok_minishell(tmp_str, "$");
	tab[j] = fill_env(tab[j], env);
	if (!tab[j])
		return (free(tab), 1);
	while (++j < i)
	{
		tab[j] = ft_strtok_minishell(NULL, "$");
		tab[j] = fill_env(tab[j], env);
		if ((i > j + 1) && !tab[j])
			return (ft_free_tab_str(tab, j), 1);
	}
	free(tmp_str);
	tkn->str = ft_strjoin_tab(tab);
	if (!tkn->str)
		return (ft_free_tab_str(tab, j), 1);
	return (0);
}

void	ft_quote_to_word(t_token *tkn)
{
	t_token	*tmp;

	tmp = tkn;
	while (tmp)
	{
		if (tmp->type == QUOTE || tmp->type == DQUOTE)
			tmp->type = WORD;
		tmp = tmp->next;
	}
}

void	ft_merge_word(t_token *tkn)
{
	t_token	*tmp;
	t_token	*save_next;

	tmp = tkn;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->next && tmp->next->type == WORD)
		{
			save_next = tmp->next->next;
			tmp->str = ft_strjoin_free(tmp->str, tmp->next->str);
			free(tmp->next);
			tmp->next = save_next;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_remove_blank_token(t_token *tkn)
{
	t_token	*tmp;
	t_token	*save_next;

	tmp = tkn;
	while (tmp)
	{
		if (tmp->next && tmp->next->type == BLANK)
		{
			save_next = tmp->next->next;
			if (tmp->next->str)
				free(tmp->next->str);
			if (tmp->next)
				free(tmp->next);
			tmp->next = save_next;
		}
		else
			tmp = tmp->next;
	}
}

/*
** ft_expand is the function that will expand the tokens
** it expands tokens of type WORD or DQUOTE in which there is a '$'
*/

int	ft_expand(t_token *tkn, t_env *env)
{
	t_token	*tmp;

	tmp = tkn;
	while (tmp)
	{
		if ((tmp->type == WORD || tmp->type == DQUOTE)
			&& ft_strchr(tmp->str, '$'))
		{
			if (ft_expand_dollar(tmp, env))
				return (1);
		}
		tmp = tmp->next;
	}
	ft_quote_to_word(tkn);
	ft_merge_word(tkn);
	ft_remove_blank_token(tkn);
	ft_delimiter_set(tkn);
	return (0);
}
