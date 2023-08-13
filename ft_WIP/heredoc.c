/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:15:22 by theophane         #+#    #+#             */
/*   Updated: 2023/08/13 18:46:21 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*is_heredoc(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_token		*is_delimiter(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == DELIMITER)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char    *ft_create_fname(char *fname)
{
    int        i;
    char    *tmp;
    char    *tmp2;
    char    *base_name;

    i = -1;
    if (fname && access(fname, F_OK))
        return (ft_strdup(fname));
    else
        base_name = ft_strjoin(fname, "_");
    while (++i >= 0 && fname && !(access(fname, F_OK)))
    {
        tmp = ft_itoa(i);
        if (i > 0)
            tmp2 = fname;
        fname = ft_strjoin(base_name, tmp);
        if (!fname)
            return (NULL);
        free(tmp);
        free(tmp2);
    }
    free(base_name);
    return (fname);
}

t_cmd   *find_heredoc_cmd(t_cmd *cmd, t_token *head)
{
    t_token *tmp;
    t_cmd   *ctmp;

    tmp = head;
    ctmp = cmd;
    while (tmp && tmp->type != HEREDOC)
    {
        if (tmp->type == PIPE)
            ctmp = ctmp->next;
        tmp = tmp->next;
    }
    if (!tmp)
        return (NULL);
    return (ctmp);
}