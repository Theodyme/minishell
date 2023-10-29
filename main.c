/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:49:22 by flplace           #+#    #+#             */
/*   Updated: 2023/10/29 14:04:07 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

char	*return_status(void)
{
	char	*str;
	char	*out;
	char	*tmp;

	str = NULL;
	out = NULL;
	tmp = ft_itoa(g_status);
	if (ft_strcmp(tmp, "0") == 0)
		out = ft_3strjoin_with_free("\033[32m", tmp, "\033[0m", 000);
	else
		out = ft_3strjoin_with_free("\033[31m", tmp, "\033[0m", 000);
	str = ft_strjoin(out, " > ");
	free(out);
	free(tmp);
	return (str);
}

void	shlvl_inc(t_env **envt)
{
	t_env	*shell;
	int		i;

	shell = ft_key_finder(envt, "SHLVL");
	if (!shell)
	{
		ft_key_add(envt, "SHLVL", "1");
		return ;
	}
	i = ft_atoi(shell->value);
	i++;
	free(shell->value);
	shell->value = ft_itoa(i);
	return ;
}

void	env_i_setup(t_env **envt)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!(*envt))
		ft_key_add(envt, "PWD", pwd);
	free(pwd);
	shlvl_inc(envt);
	return ;
}

int	cmd_setup(char *line, t_token **head, t_cmd **cmd, t_env **envt)
{
	if (ft_count_quote(line) != -1)
	*head = ft_tokenize(line);
	else
	{
		g_status = 2;
		printf(TRITON "Unmatched quote\n");
		return (1);
	}
	if (!*head)
	{
		(printf(TRITON "Tokenization failed\n"));
		return (3);
	}
	ft_expand(*head, *envt);
	*cmd = ft_parser(*head, envt);
	return (0);
}

void	main_routine(char *status, t_env *envt, t_token *head, t_cmd *cmd)
{
	char	*line;
	int		flag;

	line = NULL;
	flag = 0;
	while (true)
	{
		status = return_status();
		line = readline(status);
		free(status);
		if (!line)
			break ;
		flag = cmd_setup(line, &head, &cmd, &envt);
		if (flag == 1)
			continue ;
		else if (flag == 2)
			return ;
		ft_free_lst_token(head);
		signal(SIGINT, SIG_IGN);
		ft_exec(cmd);
		signal(SIGINT, sig_handler);
		ft_add_history(line);
		if (cmd)
			ft_free_cmd(&cmd);
	}
}

int	clear_and_exit(t_cmd *cmd, t_env *envt)
{
	ft_clear_env(envt);
	if (cmd)
		ft_free_cmd(&cmd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*status;
	t_env	*envt;
	t_cmd	*cmd;
	t_token	*head;

	(void)av;
	if (ac == 2)
		main_debug(envp);
	status = NULL;
	envt = NULL;
	cmd = NULL;
	head = NULL;
	ft_print_title1();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (ac != 1)
		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
	ft_env_reader(envp, &envt);
	env_i_setup(&envt);
	main_routine(status, envt, head, cmd);
	return (clear_and_exit(cmd, envt));
}
