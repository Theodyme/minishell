#include "minishell.h"

t_token *ft_fill_expanded(t_token *tkn, char *str)
{
	int i;
	t_token *tmp;

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

int	is_charset(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char *ft_strtok(char *str, char *delim)
{
	static char *save;
	char        *ptr;
	char        *tmp;

	if (str)
		save = str;
	if (!save || !*save)
		return (NULL);
	ptr = save;
	if (*ptr && is_charset(*ptr, delim) && *(ptr + 1) && is_charset(*(ptr + 1), "$?"))
		ptr += 2;
	else
	{
		if (*ptr && is_charset(*ptr, delim))
			ptr++;
		while (*ptr && !is_charset(*ptr, delim))
			ptr++;
	}
	tmp = ft_strndup(save, ptr - save);
		if (*ptr)
		save = ptr;
	else
		save = NULL;
	return (tmp);
}

// Marche avec les mots /!\ mais pas avec les quotes : segfault + peut compter 1 en moins avec des espaces
size_t	ft_count_part(char *str)
{
	size_t	i;
	size_t	v;

	i = 0;
	v = 0;
	if (!str)
		return (0);
	if (str[i] != '$')
	{
		v++;
		printf(".,.,.,\n");
	}
	while(str[i])
	{
		//il faut remettre des i++ hors des if
		if (is_charset(str[i], "$") && str[i + 1]  && is_charset(str[i + 1], " \t\n")  && ++i)
		{
			printf("++++\n");
			v++;
			if (str[i] && !is_charset(str[i], "$"))
			{
				printf("****\n");
				v++;
			}	
		}
		else if (is_charset(str[i], "$") && str[i + 1]  && is_charset(str[i + 1], "$? \t") && ++i  && ++i)
		{
			printf("____\n");
			v++;
			if (str[i] && !is_charset(str[i], "$"))
			{
				printf("----\n");
				v++;
			}	
		}
		if (is_charset(str[i], "$"))
		{
			printf("======\n");
			v++;
		}
		i++;
	}
	printf("=====> v = %zu\n", v);
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
	if (*str != '$')
		out = strdup(str);
	str++;
	if (!out && !(*str))
		out = strdup("$");
	if (!out && *str == '?')
		out = ft_itoa(7777777);
	if (!out && *str == '$')
		out = ft_itoa(9999999);
	else if (!out)
		out = ft_getvalue(str, env);
	free(dent);
	return (out);
}
// DECOUPER EN MOTS *PUIS* EXPAND quand il y a un $
int ft_expand_dollar_inword(t_token *tkn, t_env *env) 
{ 
	t_token	*save_next;
	char	**tab;
	char    *tmp_str;
	size_t	i;
	size_t	j;

	i = ft_count_part(tkn->str);
	j = 0;
	tab = ft_calloc(i + 1, sizeof(char *));
	tmp_str = tkn->str;
	save_next = tkn->next;
	tab[j] = ft_strtok(tmp_str, "$");
	tab[j] = fill_env(tab[j], env);
	while(++j < i)
	{	
		tab[j] = ft_strtok(NULL, "$");
		tab[j] = fill_env(tab[j], env);
	}
	free(tmp_str);
	tkn->str = ft_strjoin_tab(tab);
	tkn->next = save_next;
	return (0);
}

/*
** ft_expand is the function that will expand the tokens
** it expands tokens of type WORD or DQUOTE in which there is a '$'
** Function is general purpose will allow expansion of more things in more contexts
*/

int ft_expand(t_token *tkn, t_env *env)
{
	t_token *tmp;

	tmp = tkn;
	while (tmp)
	{
		if (tmp->type == WORD && ft_strchr(tmp->str, '$'))
		{
			if(ft_expand_dollar_inword(tmp, env))
				return (0);
		}
		else if (tmp->type == DQUOTE && ft_strchr(tmp->str, '$'))
		{
			if(ft_expand_dollar_inword(tmp, env))
		        return (1);
		}
		tmp = tmp->next;
	}
	printf("\n=====> ft_expand\n");
	ft_print_token(tkn);
	return (0);
}

// il coupe en $ et en ~ et extend les $ mais pas les ~ sauf si c'est le premier char
// attention si rien apres le $ ca expand pas