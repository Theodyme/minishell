
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:45:17 by flplace           #+#    #+#             */
/*   Updated: 2023/02/02 17:52:42 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_bltin_tester(t_cmd *cmd)
{
	int			i;
	const t_fn	bltin[7] = {
	{.call = "echo", .blt_fn = &ft_bltin_echo},
	{.call = "cd", .blt_fn = &ft_bltin_cd},
	{.call = "pwd", .blt_fn = &ft_bltin_pwd},
	{.call = "export", .blt_fn = &ft_bltin_export},
	{.call = "unset", .blt_fn = &ft_bltin_unset},
	{.call = "env", .blt_fn = &ft_bltin_env},
	{.call = "exit", .blt_fn = &ft_bltin_exit}, // A AJOUTER
	};

	i = 0;
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	while(ft_strcmp(bltin[i].call, cmd->name) != 0 && bltin[i].call)
		i++;
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (1);
	if (ft_strcmp(bltin[i].call, "\0") != 0)
		return (bltin[i].blt_fn(cmd));
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char 	*line = NULL;
	t_env	*envt = NULL;
	t_cmd	*cmd = NULL;

	t_token	*head;

	if (ac != 1 && av)
		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
	ft_env_reader(envp, &envt);
	if (!envt)
	{
		write(2, "Error: Couldn't get env variables\n", 34);
		return 1;
	}
	while (true)
	{
		line = readline("$> ");
		if (!line)
			break ;
		// if (ft_strcmp(line, "exit") == 0)
		// {
		// 	free(line);
		// 	ft_free_lst_env(envt);
		// 	break ;
		// }
		if (ft_count_quote(line) != -1)
			head = ft_tokenize(line);
		else
		{
			write(2, "Error: Unmatched quote\n", 23);
			continue ;
		}
		printf("Tokenization done\n");
		ft_print_token(head);
		if (!head)
			return (write(2, "Error: Tokenization failed\n", 27), 1);
		ft_expand(head, envt);
		cmd = ft_parser(head);
		if (cmd)
			continue ;
		if (ft_bltin_tester(cmd) == 1)
		{
			free(line);
			ft_free_lst_env(envt);
			break ;
		}
		ft_add_history(line);
		ft_free_lst_token(head);
		write(1, "\n", 1);
	}
	return (0);
}
