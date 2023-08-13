/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:42:18 by mabimich          #+#    #+#             */
/*   Updated: 2023/07/26 15:58:06 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (ft_is_in_charset(*ptr, delim))
	{
		ptr++;
		if (*ptr && ft_is_in_charset(*ptr, "0123456789?$"))
			ptr++;
		else if (*ptr && ft_is_in_charset(*ptr, C_ALPHA) && ptr++)
			while (*ptr && ft_is_in_charset(*ptr, C_ALPHANUM))
				ptr++;
	}
	else
		while (*ptr && !ft_is_in_charset(*ptr, delim))
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
		if (ft_is_in_charset(str[i], "$"))
		{
			i++;
			if (str[i] && ft_is_in_charset(str[i], "0123456789?$"))
				i++;
			else if (str[i] && ft_is_in_charset(str[i], C_ALPHA) && i++)
				while (str[i] && ft_is_in_charset(str[i], C_ALPHANUM))
					i++;
		}
		else
			while (str[i] && !ft_is_in_charset(str[i], "$"))
				i++;
	}
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
		out = ft_itoa(WEXITSTATUS(g_status));
	else if (!out)
		out = ft_getvalue(str, env);
	free(dent);
	return (out);
}
