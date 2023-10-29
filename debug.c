#include "minishell.h"

int	main_debug(char **envp)
{
	char	*line = NULL;
	char	*status = NULL;
	t_env	*envt = NULL;
	t_cmd	*cmd = NULL;
	t_token	*head;

	ft_print_title1();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_env_reader(envp, &envt);
	env_i_setup(&envt);
	g_status = 0;
	while (true)
	{
		status = return_status();
		line = readline(status);
		free(status);
		if (!line)
			break ;
		if (ft_count_quote(line) != -1)
			head = ft_tokenize(line);
		else
		{
			g_status = 2;
			write(2, "TRITONUnmatched quote\n", 23);
			continue ;
		}
		printf("Tokenization done\n");
		ft_print_token(head);
		if (!head)
			return (write(2, "TRITONTokenization failed\n", 27), 1);
		ft_expand(head, envt);
		printf("\nExpansion done\n");
		ft_print_token(head);
		cmd = ft_parser(head, &envt);
		ft_free_lst_token(head);
		printf("Parsing done\n");
		ft_print_cmd(cmd);
		signal(SIGINT, SIG_IGN);
		ft_exec(cmd);
		signal(SIGINT, sig_handler);
		ft_add_history(line);
		if (cmd)
			ft_free_cmd(&cmd);
	}
	ft_clear_env(envt);
	if (cmd)
		ft_free_cmd(&cmd);
	exit(0);
}// }
