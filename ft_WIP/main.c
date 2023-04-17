
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

void	ft_print_title(void)
{
	printf("_____________________________________________________________________________________\n\n");
	printf("        W e l c o m e   t o          \n");
	printf("                                     _.---._\n");
	printf("\033[34m '||    ||'  ||            ||  \033[0m  .'''.'/|%c`.'''.   \033[33m       '||              '||  '||  \033[0m\n", 92);
	printf("\033[34m  |||  |||  ...  .. ...   ...  \033[0m :  .' / | %c `.  :  \033[33m ....   || ..     ....   ||   ||  \033[0m\n", 92);
	printf("\033[34m  |'|..'||   ||   ||  ||   ||  \033[0m '.'  /  |  %c  `.'  \033[33m||. '   ||' ||  .|...||  ||   ||  \033[0m\n", 92);
	printf("\033[34m  | '|' ||   ||   ||  ||   ||  \033[0m  `. /   |   %c .'   \033[33m. '|..  ||  ||  ||       ||   ||  \033[0m\n", 92);
	printf("\033[34m .|. | .||. .||. .||. ||. .||. \033[0m    `-.__|__.-'     \033[33m|'..|' .||. ||.  '|...' .||. .||. \033[0m\n\n");
	printf("                                      \033[33mm a b i m i c h \033[0m    &&    \033[34mf l p l a c e \033[0m\n");
	printf("_____________________________________________________________________________________\n\n");
	return ;
}

int ft_bltin_tester(t_cmd **cmd)
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
		return (2);
	while(bltin[i].call && ft_strcmp(bltin[i].call, (*cmd)->name) != 0)
		i++;
	(*cmd)->pid = 1;
	if (ft_strcmp((*cmd)->name, "exit") == 0)
		return (2);
	if (bltin[i].call)
	{
		(*cmd)->status = bltin[i].blt_fn(*cmd);
		return (1);
	}
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

char	*return_status(void)
{
	char	*str = NULL;
	char	*out = NULL;
	char	*tmp = NULL;

	tmp = ft_itoa(WEXITSTATUS(g_status));
	if (ft_strcmp(tmp, "0") == 0)
		out = ft_3strjoin_with_free("\033[32m", tmp, "\033[0m", 000);
	else
		out = ft_3strjoin_with_free("\033[31m", tmp, "\033[0m", 000);
	str = ft_strjoin(out, " > ");
	free(tmp);
	return (str);
}

int		g_status = 0;

int	main(int ac, char **av, char **envp)
{
	int 	debug = 0;
	char	*line = NULL;
	char*	status = NULL;
	t_env	*envt = NULL;
	t_cmd	*cmd = NULL;

	t_token	*head;

	ft_print_title();
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
		status = return_status();
		line = readline(status);
		free(status);
		g_status = 0;
		if (!line)
			break ;
		if (ft_count_quote(line) != -1) // penser a add history
			head = ft_tokenize(line);
		else
		{
			write(2, "Bash: Unmatched quote\n", 23);
			continue ;
		}
		if (debug)
		{
		printf("Tokenization done\n");
		ft_print_token(head);
		}
		if (!head)
			return (write(2, "Bash: Tokenization failed\n", 27), 1);
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
		ft_exec(cmd);
		ft_add_history(line);
		ft_free_lst_token(head);
	}
	return (0);
}
