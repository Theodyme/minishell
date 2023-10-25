/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:42:18 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/25 22:06:50 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_getvalue(char *key, t_env *env, int type)
{
	char	*value;

	while (env)
	{
		if (!ft_strcmp(key, env->key))
		{
			if (type == WORD)
				value = trim_to_export(env->value);
			else if (type == DQUOTE)
				value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	if (!env)
		value = ft_strdup("");
	return (value);
}

char	*fill_env(char *str, t_env *env, int type)
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
		out = ft_itoa(g_status);
	else if (!out)
		out = ft_getvalue(str, env, type);
	free(dent);
	return (out);
}
