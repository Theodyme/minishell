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
    if (*ptr && is_charset(*ptr, delim))
	 	ptr++;
	if (*ptr && is_charset(*ptr, delim))
	 	ptr++;
    while (*ptr && !is_charset(*ptr, delim))
        ptr++;
    tmp = ft_strndup(save, ptr - save);
    if (*ptr)
        save = ptr;
    else
        save = NULL;
    return (tmp);
}

size_t	ft_count_part(char *str)
{
	size_t	i;
	size_t	v;

	i = 0;
	v = 0;
	while(str[i])
	{
		if (is_charset(str[i], "$") && str[i + 1] && !is_charset(str[i + 1], "$"))
			v++;
		i++;
	}
	return (v);
}

char	*ft_getvalue(char *key, t_env *env)
{
	char	*value;

	printf("start ft_getvalue\n");
	while (env)
	{
		printf("key: %s, env->key: %s\n", key, env->key);
		if (!ft_strcmp(key, env->key))
		{
			value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	if (!env)
		value = ft_strdup("");
	printf("end ft_getvalue\n");
	return (value);
}

char	*fill_env(char *str, t_env *env)
{
	char	*dent;
	char	*out;

	dent = str;
	if (*str != '$')
		out = strdup("");
	printf("dent: %s\n", dent);
	str++;
	if (*str == '?')
		out = ft_itoa(7777777);
	else if (*str == '$')
		out = ft_itoa(9999999);
	else
		out = ft_getvalue(str, env);
	printf("dent2: %s\n", dent);
	free(dent);
	return (out);
}

int ft_expand_dollar_inword(t_token *tkn, t_env *env) // DECOUPER EN MOTS *PUIS* EXPAND quand il y a un $
{ // puis encore plus tard 

	/*   if (tkn->str[1] == '?')
	{
		tkn->str = ft_itoa(env->status);
		return (1);
	}
	else if (tkn->str[1] == '$')
	{
		tkn->str = ft_itoa(env->pid);
		return (1);
	}
	else if (tkn->str[1] == '!')
	{
		tkn->str = ft_itoa(env->pid);
		return (1);
	}*/

	t_token *save_next;
	int	i;

	i = ft_count_part(tkn->str);
//    char    *key;
	char    *tmp_str;
	(void)env;

	tmp_str = tkn->str;
	save_next = tkn->next;
//	printf("tmp_str====>%s|\ntkn_str--->%s|\n", tmp_str, tkn->str);
//	printf("NEXT_str = %s|\n", tkn->next->str);
	if (tkn->str[0] == '$' && i--)
		tkn->type = DOLLAR;
	
	tkn->str = ft_strtok(tmp_str, "$");
	if (tkn->type == DOLLAR)
		tkn->str = fill_env(tkn->str, env);
	printf("i_dollar=%d, tkn_str = %s\n", i, tkn->str);
	while(i-- > 0)
	{	
		tkn->next = ft_calloc(1, sizeof(t_token));
		tkn = tkn->next;
		tkn->type = DOLLAR;
		tkn->str  = ft_strtok(NULL, "$");
		printf("test_loop3\n");
		tkn->str = fill_env(tkn->str, env);
		printf("end_loop, tmp_str = %s\n", tkn->str);
	}
	//   free(key);
	free(tmp_str);
	tkn->next = save_next;
	printf("end_function\n");
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
            if(ft_expand_dollar_inword(tmp, env))
                return (0);
        // else if (tmp->type == DQUOTE && tmp->str, '$')
        //     if(ft_expand_dollar_inquote(tmp, env))
        //         return (1);

		
        tmp = tmp->next;
		printf("end_while in ft_expand\n");
	}
	ft_print_token(tkn);
    return (0);
}

// il coupe en $ et en ~ et extend les $ mais pas les ~ sauf si c'est le premier char
// attention si rien apres le $ ca expand pas