#include "minishell.h"

t_token	*ft_fill_expanded(t_token *tkn, char *str)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = tkn;
	free(tkn->str);
	while (str[i])
	{
		i += ft_trim_blank(str + i);
		tmp->type = WORD;
		tmp->str = ft_strndup(str + i, ft_wordlen(str + i));
		i += ft_wordlen(str + i);
		tmp->next = ft_calloc(1, sizeof(t_token));
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
	}
	tmp->next = tkn->next;
	return (tkn);
}

char	*ft_strtok_minishell(char *str, char *delim)
{
	static char	*save;
	char		*ptr;
	char		*tmp;

	if (str)
		save = str;
	if (!save || !*save)
		return (NULL);
	ptr = save;
	if (ft_is_charset(*ptr, delim))
	{
		ptr++;
		if (*ptr && ft_is_charset(*ptr, "$?"))
			ptr++;
		else if (*ptr && ft_is_charset(*ptr, ALPHA) && ptr++)
			while (*ptr && ft_is_charset(*ptr, ALPHANUM))
				ptr++;
	}
	else
		while (*ptr && !ft_is_charset(*ptr, delim))
			ptr++;
	tmp = ft_strndup(save, ptr - save);
	save = ptr;
	return (tmp);
}

size_t	ft_count_part(char *str)
{
	size_t	i;
	size_t	v;

	i = 0;
	v = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		v++;
		if (ft_is_charset(str[i], "$"))
		{
			i++;
			if (str[i] && ft_is_charset(str[i], "$?"))
				i++;
			else if (str[i] && ft_is_charset(str[i], ALPHA) && i++)
				while (str[i] && ft_is_charset(str[i], ALPHANUM))
					i++;
		}
		else
			while (str[i] && !ft_is_charset(str[i], "$"))
				i++;
	}
	printf("\t--> v = %zu\n", v);
	return (v);
}

char	*ft_getvalue(char *key, t_env *env)
{
	char	*value;

	while (env)
	{
		if (!ft_strcmp(key, env->key))
		{
			value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	if (!env)
		value = ft_strdup("");
	return (value);
}

char	*fill_env(char *str, t_env *env)
{
	char	*dent;
	char	*out;

	dent = str;
	out = NULL;
	if (!str)
		return (NULL);
	if (*str != '$')
		out = strdup(str);
	str++;
	if (!out && !(*str))
		out = strdup("$");
	if (!out && *str == '?')
		out = ft_itoa(7777777);
	else if (!out)
		out = ft_getvalue(str, env);
	free(dent);
	return (out);
}

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

void	ft_remove_blank(t_token *tkn)
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
** Function is general purpose will allow expansion of more things in more contexts
*/

int	ft_expand(t_token *tkn, t_env *env)
{
	t_token	*tmp;

	tmp = tkn;
	while (tmp)
	{
		if (tmp->type == WORD && ft_strchr(tmp->str, '$'))
		{
			printf("WORD: %s\n", tmp->str);
			if (ft_expand_dollar(tmp, env))
				return (1);
		}// merge au dessus et en dessous
		else if (tmp->type == DQUOTE && ft_strchr(tmp->str, '$'))
		{
			printf("DQUOTE: %s\n", tmp->str);
			if (ft_expand_dollar(tmp, env))
				return (1);
		}
		tmp = tmp->next;
	}
	ft_quote_to_word(tkn);
	ft_merge_word(tkn);
	ft_remove_blank(tkn);
	printf("\n=====> ft_expand\n");
	ft_print_token(tkn);
	return (0);
}
