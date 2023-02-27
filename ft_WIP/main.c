
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

void ft_bltin_tester(char **line, t_env **envt)
{
	t_cmd_div	*div;

	div = (t_cmd_div *)malloc(sizeof(t_cmd_div));
	div->envt = *envt;
	if (ft_strcmp(*line, "env") == 0)
	{
		if (envt)
			ft_bltin_env(div);
		else
			printf("env error: nothing to print.\n");
	}
	else if (ft_strcmp(*line, "pwd") == 0)
		ft_bltin_pwd(div);
	else if (ft_strcmp(*line, "unset USER") == 0)
		ft_bltin_unset(div);
	else if (ft_strcmp(*line, "unset USE") == 0)
		ft_bltin_unset(div);
	else if (ft_strcmp(*line, "unset USER0") == 0)
		ft_bltin_unset(div);
	else if (ft_strcmp(*line, "unset HELLO") == 0)
		ft_bltin_unset(div);
	else if (ft_strcmp(*line, "unset LAST") == 0)
		ft_bltin_unset(div);
	else if (ft_strcmp(*line, "clear") == 0)
	{
		ft_clear_env(div->envt);
		*envt = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	char 	*line = NULL;
	t_env	*envt = NULL;

	t_token	*head;

	if (ac != 1 && av)
		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
	// head = ft_calloc(1, sizeof(t_token));
	// if (!head)
		// return 1;
	ft_env_reader(envp, &envt);
	if (!envt)
	{
		write(1, "Error: Couldn't get env variables\n", 34);
		return 1;
	}
	while (true)
	{
		line = readline(ft_strdup("$> "));
		if (!line)
			break ;
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		else
			ft_bltin_tester(&line, &envt);
		if (ft_count_quote(line) != -1)
			head = ft_tokenize(line);
		else
			write(2, "Error: Unmatched quote\n", 23);
		// if (!head)
		// 	return (write(2, "Error: Tokenization failed\n", 27), 1);
		//	ft_testmodif(head);
		//ft_expand(head, envt);
		ft_add_history(line);
		write(1, "\n", 1);
	}
	return (0);
}
