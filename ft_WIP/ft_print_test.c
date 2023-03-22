#include "minishell.h"

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	printf("_PRINT ARRAY_\n");
	while (array && array[i])
	{
		printf("array[%d]: %s\n", i, array[i]);
		i++;
	}
	printf("\n");
}

void	ft_print_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*tmp;

	i = 0;
	printf("_____PRINTING CMD______\n");
	while (cmd)
	{
		printf("name: %s\n", cmd->name);
		tmp = cmd->redir;
		while (tmp)
		{
			printf("redirect type: %d --> file: %s\n", tmp->type, tmp->file);
			tmp = tmp->next;
		}
		ft_print_array(cmd->argv);
		cmd = cmd->next;
		printf("__________%d_____________\n\n",i++);
	}
}

void	ft_print_token(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("type: %d, str: |%s|\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
}

void	ft_print_env(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp->next)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
