/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:37:22 by theophane         #+#    #+#             */
/*   Updated: 2023/08/17 06:01:11 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	return ;
}

void	ft_free_lst_token(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

void	ft_free_args(t_cmd *cmd)
{
	t_arg	*tmp;
	t_arg	*node;

	tmp = cmd->args_list;
	if (cmd->argv)
	{
		ft_free_tab_str(cmd->argv, -1);
		cmd->argv = NULL;
	}
	if (cmd->envp)
	{
		ft_free_tab_str(cmd->envp, -1);
		cmd->envp = NULL;
	}
	while (tmp)
	{
		free(tmp->str);
		node = tmp;
		tmp = tmp->next;
		free(node);
	}
	return ;
}

void	free_heredoc(t_redir *rdr)
{
	unlink(rdr->file);
	free(rdr->delimiter);
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_redir	*tmp;
	t_redir	*node;
	t_cmd	*ctmp;
	t_cmd	*cnode;

	ctmp = cmd;
	while (ctmp)
	{
		free(ctmp->name);
		tmp = ctmp->redir;
		while (tmp)
		{
			if (tmp->type && tmp->type == HEREDOC)
				free_heredoc(tmp);
			free(tmp->file);
			node = tmp;
			tmp = tmp->next;
			free(node);
		}
		ft_free_args(ctmp);
		cnode = ctmp;
		ctmp = ctmp->next;
		free(cnode);
	}
	return ;
}
