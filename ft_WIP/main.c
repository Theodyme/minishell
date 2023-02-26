
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

int main(int ac, char **av, char **envp)
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
		write(2, "Error: Couldn't get env variables\n", 34);
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
			ft_free_lst_env(envt);
			break ;
		}
	/*	if (ft_strcmp(line, "env") == 0)
		{
			env_printer(&envt);	
			free(line);
		}
	*/	if (ft_count_quote(line) != -1)
			head = ft_tokenize(line);
		else
			write(2, "Error: Unmatched quote\n", 23);
		printf("Tokenization done\n");
		ft_print_token(head);
		if (!head)
			return (write(2, "Error: Tokenization failed\n", 27), 1);
		ft_add_history(line);
		ft_expand(head, envt);
		ft_free_lst_token(head);
		write(1, "\n", 1);
	}
	return (0);
}
