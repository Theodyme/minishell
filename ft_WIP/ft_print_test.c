#include "minishell.h"

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		printf("array[%d]: %s\n", i, array[i]);
		i++;
	}
}
void	ft_print_cmd(t_cmd *cmd)
{
	t_cmd	*start;
	//t_arg	*tmp;
	t_redir	*tmp2;

	start = cmd;
	printf("_____PRINTING CMD______\n");
	while (cmd)
	{
		printf("name: %s\n", cmd->name);
		//tmp = cmd->args_list;
		// while (tmp)
		// {
		// 	printf("arg: %s\n", tmp->str);
		// 	tmp = tmp->next;
		// }
		tmp2 = cmd->redir;
		while (tmp2)
		{
			printf("redirect type: %d --> file: %s\n", tmp2->type, tmp2->file);
			tmp2 = tmp2->next;
		}
		ft_print_array(cmd->args);
		cmd = cmd->next;
		printf("_______________________\n");
	}
	cmd = start;
}
void ft_print_token(t_token *head)
{
	t_token *tmp;

	tmp = head;
	while (tmp)
	{
		printf("type: %d, str: |%s|\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
}

void ft_print_env(t_env *head)
{
	t_env *tmp;

	tmp = head;
	while (tmp->next)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
