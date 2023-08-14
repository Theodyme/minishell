/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:15:22 by theophane         #+#    #+#             */
/*   Updated: 2023/08/14 15:52:54 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*is_heredoc(t_token *head)
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

t_token	*is_delimiter(t_token *head)
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

t_cmd	*find_heredoc_cmd(t_cmd *cmd, t_token *head)
{
	t_token	*tmp;
	t_cmd	*ctmp;

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
