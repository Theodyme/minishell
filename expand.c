/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:34:12 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/25 22:46:06 by mabimich         ###   ########.fr       */
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
	tab[j] = fill_env(tab[j], env, tkn->type);
	if (!tab[j])
		return (free(tab), 1);
	while (++j < i)
	{
		tab[j] = ft_strtok_minishell(NULL, "$");
		tab[j] = fill_env(tab[j], env, tkn->type);
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

int	ft_create_two_tkn_for_split_wtkn(t_token *tkn, char *str, int *i)
{
	t_token	*save_next;

	save_next = tkn->next;
	tkn->next = ft_calloc(1, sizeof(t_token));
	if (!tkn->next)
		return (1);
	tkn = tkn->next;
	tkn->str = ft_strdup(" ");
	if (!tkn->str)
		return (1);
	tkn->type = BLANK;
	tkn->next = ft_calloc(1, sizeof(t_token));
	if (!tkn->next)
		return (1);
	tkn = tkn->next;
	tkn->str = ft_strndup(&str[*i], ft_strsetlen(&str[*i], C_BLANK));
	tkn->next = save_next;
	tkn->type = QUOTE;
	*i += ft_strsetlen(&str[*i], C_BLANK) + 1;
	return (0);
}

int	ft_split_wordtoken(t_token *tkn)
{
	t_token	*save_next;
	char	*save;
	int		i;

	if (!tkn)
		return (1);
	if (tkn->type != WORD || !ft_strchrset(tkn->str, C_BLANK))
		return (0);
	save = tkn->str;
	save_next = tkn->next;
	i = ft_strsetlen(save, C_BLANK) + 1;
	tkn->str = ft_strndup(save, ft_strsetlen(save, C_BLANK));
	if (!tkn->str)
		return (1);
	while (save && save[i - 1])
	{	
		if (ft_create_two_tkn_for_split_wtkn(tkn, save, &i))
			return (1);
		if (tkn->next->next)
			tkn = tkn->next->next;
		else
			return (1);
	}
	free(save);
	return (tkn->next = save_next, 0);
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
			if (ft_split_wordtoken(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	ft_quote_to_word(tkn);
	ft_merge_word(tkn);
	ft_remove_blank_token(tkn);
	return (0);
}
