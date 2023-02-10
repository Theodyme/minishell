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

    t_token *save;
    char    *key;
    char    *tmp_str;
    char    *ptr1;
    char    *ptr2;

    tmp_str = tkn->str;
	ptr1 = tmp_str;
    ptr2 = tmp_str;
    save = tkn->next;
    

    free(tkn->str);
    while(*ptr2)
    {
        if (tmp_str[0] == '$')
        {
            key = ft_strndup(ptr2, ft_wordlen_with_dollar(ptr2));
            if (ft_getenv(key, env))
            {
                tkn->str = ft_strdup(ft_getenv(key, env));
                tkn->next = ft_fill_expanded(tkn, ptr2);
                return (1);
            }
            else
            {
                tkn->str = ft_strdup("");
                tkn->next = ft_fill_expanded(tkn, ptr2);
                return (1);
            }
        }
        while (*ptr2 && *ptr2 != '$')
            ptr2++;
        tkn->str = ft_strndup(ptr1, ptr2 - ptr1);
        tkn->next = ft_calloc(1, sizeof(t_token));
        if (!tkn->next)
            return (1);
        tkn = tkn->next;
        if (*ptr2 == '$')
        {
            ptr2++;
            key = ft_strndup(ptr2, ft_wordlen_with_dollar(ptr2));
            if (ft_getenv(key, env))
            {
                tkn->str = ft_strdup(ft_getenv(key, env));
                tkn->next = ft_fill_expanded(tkn, ptr2);
                return (1);
            }
            else
            {
                tkn->str = ft_strdup("");
                tkn->next = ft_fill_expanded(tkn, ptr2);
                return (1);
            }
        }
        else
        {
            tkn->next = ft_calloc(1, sizeof(t_token));
            if (!tkn->next)
                return (0);
            tkn = tkn->next;
        }
        ptr1 = ptr2;
    }
    free(key);
    free(tmp);

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
        if (tmp->type == WORD && tmp->str, '$')
            ft_expand_dollar_inword(tmp, env);
        else if (tmp->type == DQUOTE && tmp->str, '$')
            ft_expand_dollar_inquote(tmp, env);
        tmp = tmp->next;
    }
    return (1);
}