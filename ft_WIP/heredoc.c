/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:15:22 by theophane         #+#    #+#             */
/*   Updated: 2023/08/10 18:28:41 by theophane        ###   ########.fr       */
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

void    ft_heredoc_cat(char *line, t_token *head, t_cmd *cmd)
{
    // t_cmd   *tmp;
    t_arg   *tmp;
    // int     i;

/////////////////// print args_list
    tmp = (find_heredoc_cmd(cmd, head))->args_list;
    if (!tmp)
    {
        tmp = ft_calloc(1, sizeof(t_arg));
        if (!tmp)
        {
            printf("Error: ft_create_arg failed\n");
            return ;
        }
    }
    else
    {
        while (tmp && tmp->str)
            tmp = tmp->next;
    }
	if (ft_add_arg(tmp, line))
		{
            printf("Error: ft_add_arg failed\n");
            return ;
        }
    printf("added : ''%s'' to the args list\n", tmp->str);
    // if (!tmp->argv)
	// 	tmp->argv = ft_calloc(1 + 1, sizeof(char *));
    // while (tmp->argv[i] && tmp->argv[i][0])
    // {
    //     i++;
    // }
    // tmp->argv[i] = ft_strdup(line);
    free(line);
	line = NULL;
    return ;
}