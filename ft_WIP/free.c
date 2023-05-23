#include "minishell.h"

void	ft_free_array(char **array)
{
	int i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	return ;
}

void	ft_free_args(t_cmd *cmd)
{
	t_arg	*tmp;
	t_arg	*node;

	tmp = cmd->args_list;
	if (cmd->argv)
	{
		ft_free_array(cmd->argv);
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
		ctmp = ctmp->next;
	}
	free(cmd);
	return ;
}
