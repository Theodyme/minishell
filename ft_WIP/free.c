/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:37:22 by theophane         #+#    #+#             */
/*   Updated: 2023/08/14 15:54:00 by flplace          ###   ########.fr       */
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
		ft_free_array(cmd->argv);
		if (cmd->argv)
			free(cmd->argv);
		cmd->argv = NULL;
	}
	ft_free_array(cmd->envp);
	cmd->envp = NULL;
	ft_free_array(cmd->name_file);
	while (tmp)
	{
		free(tmp->str);
		node = tmp;
		tmp = tmp->next;
		free(node);
	}
	return ;
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
			free(tmp->file);
			node = tmp;
			tmp = tmp->next;
			free(node);
		}
		ft_free_args(ctmp);
		cnode = ctmp;
		ctmp = ctmp->next;
		if (cnode)
			free(cnode);
	}
	return ;
}
