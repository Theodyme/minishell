#include "minishell.h"

int ft_fill_expanded(t_token *tkn, char *str)
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

int ft_expand_dollar(t_token *tkn, t_env *env)
{
    t_token *save;
    char    *key;
    char    *tmp;

    save = tkn->next;
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
    key = ft_strdup(tkn->str + 1);
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            tkn = ft_fill_expanded(tkn, env->value);
            tkn->next = save;
        }
        env = env->next;
    }
    free(key);
    free(tmp);


}

int ft_expand(t_token *lst, t_env *env)
{
    t_token *tmp;
    t_token *mem;

    tmp = lst;
    while (tmp)
    {
        if (tmp->type == WORD || tmp->type == DQUOTE)
        {
            if (tmp->str[0] == '$')
                tmp->str = ft_expand_dollar(tmp, env);
        }
        tmp = tmp->next;
    }
    return (1);
}