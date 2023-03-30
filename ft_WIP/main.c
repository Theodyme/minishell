
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

int		ft_bltin_tester(t_cmd **cmd)
{
	int			i;
	const t_fn	bltin[8] = {
	{.call = "echo", .blt_fn = &ft_bltin_echo},
	{.call = "cd", .blt_fn = &ft_bltin_cd},
	{.call = "pwd", .blt_fn = &ft_bltin_pwd},
	{.call = "export", .blt_fn = &ft_bltin_export},
	{.call = "unset", .blt_fn = &ft_bltin_unset},
	{.call = "env", .blt_fn = &ft_bltin_env},
	{.call = "exit", .blt_fn = &ft_bltin_exit},
	};

	i = 0;
	if (!(*cmd)->name)
		return (0);
	while(bltin[i].call&& ft_strcmp(bltin[i].call, (*cmd)->name) != 0)
		i++;
	if (ft_strcmp((*cmd)->name, "exit") == 0)
		return (1);
	if (bltin[i].call)
		bltin[i].blt_fn(*cmd);
	return (0);
}

void	ft_setting_env(t_env *envt, t_cmd *cmd)
{
	t_cmd	*tmp;

	if(!envt)
		return ;
	tmp = cmd;
	while(tmp)
	{
		tmp->envt = envt;
		tmp = tmp->next;
	}
}

int		g_status = 0;

int	main(int ac, char **av, char **envp)
{
	int 	debug = 0;
	char	*line = NULL;
	t_env	*envt = NULL;
	t_cmd	*cmd = NULL;
	t_cmd	*tmp = NULL;

	t_token	*head;

	if (ac != 1 && ac != 2)// && av)  attention a remettre a 1
		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
	if (ac == 2)
		debug = atoi(av[1]); // a enlever
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
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			ft_free_lst_env(envt);
			break ;
		}
		if (ft_count_quote(line) != -1)
			head = ft_tokenize(line);
		else
		{
			write(2, "Error: Unmatched quote\n", 23);
			continue ;
		}
		if (debug)
		{
		printf("Tokenization done\n");
		ft_print_token(head);
		}
		if (!head)
			return (write(2, "Error: Tokenization failed\n", 27), 1);
		ft_expand(head, envt);
		if (debug)
		{
			printf("Expansion done\n");
			ft_print_token(head);
		}
		cmd = ft_parser(head, envt);
		ft_setting_env(envt, cmd);
		if (debug)
		{
			printf("Parsing done\n");
			ft_print_cmd(cmd);
		}
		tmp = cmd;
		while (tmp)
		{
			if (ft_bltin_tester(&tmp) == 1)
			{
				free(line);
				//ft_free_lst_env(envt);
				break ;
			}
			tmp = tmp->next;
		}
		ft_exec(cmd);
		ft_add_history(line);
		ft_free_lst_token(head);
	}
	return (0);
}
