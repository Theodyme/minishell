/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:49:22 by flplace           #+#    #+#             */
/*   Updated: 2023/10/24 19:25:53 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	ft_print_title2(void)
{
	printf(BL "                                       ");
	printf(" ⠈⠛⢿⣿⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀" WH "\n");
	printf("        ᵃ ᵐᶦⁿᶦˢʰᵉˡˡ ᵖʳᵒʲᵉᶜᵗ" BL "          ");
	printf("       ⠐⠺⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠟⠋⠉⠀⠀⠀⠀" WH "\n");
	printf("        ᵇʸ   ᵐᵃᵇᶦᵐᶦᶜʰ" BL "                 ");
	printf("            ⠈⠉⢹⣿⣿⡿⢿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀" WH "\n");
	printf("        ᵃⁿᵈ  ᶠˡᵖˡᵃᶜᵉ" BL "                     ");
	printf("           ⠘⣿⡟⠀⠀⠈⠛⠿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" WH "\n");
	printf(BL "_____________________________________________");
	printf("____________________________" WH "\n\n");
	return ;
}

void	ft_print_title1(void)
{
	printf(BL "____________________________________");
	printf("_____________________________________" WH "\n\n");
	printf("        ᴡ ᴇ ʟ ᴄ ᴏ ᴍ ᴇ    ᴛ ᴏ \n\n");
	printf("        " GR "|''||''|               ||");
	printf(BL "   ⠁⠁⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠹           ⠲⣦⣄⠀" WH "\n");
	printf("        " GR "   ||            ''    ||");
	printf(BL "                  ⠘             ⠙⣷⣄⠀⠀" WH "\n");
	printf("        " GR "   ||    '||''|  ||  ''||''  .|'");
	printf("'|, `||''|," BL "               ⣿⣿⣦⠀" WH "\n");
	printf("        " GR "   ||     ||     ||    ||    ");
	printf("||  ||  ||  ||" BL "        ⢀    ⢀⣼⠿⠛⢻⣆" WH "\n");
	printf("        " GR "  .||.   .||.   .||.   `|..' `");
	printf("|..|' .||  ||." BL "     ⢀⣴⡿       ⢀⣼⡿ " WH "\n");
	printf(BL "       ⡄                             ");
	printf("                  ⣠⣾⣿⣿⣇  ⢀⣀⣠⣶⣾⣿⣿⠃" WH "\n");
	printf(BL "       ⣆⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⡀⡀⡀  ");
	printf("    ⢀⣀⣀⣀⣠⣤⣤⣤⣶⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀" WH "\n");
	ft_print_title2();
	return ;
}

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
	if (!envt)
	{
		write(2, "Error: Couldn't get env variables\n", 34);
		return (1);
	}
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
}

int	main(int ac, char **av, char **envp)
{
	char	*line = NULL;
	char	*status = NULL;
	t_env	*envt = NULL;
	t_cmd	*cmd = NULL;
	t_token	*head;

	(void)av;
	if (ac == 2)
		main_debug(envp);
	ft_print_title1();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (ac != 1)
		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
	ft_env_reader(envp, &envt);
	env_i_setup(&envt);
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
			printf(TRITON "Unmatched quote\n");
			continue ;
		}
		if (!head)
			return (printf(TRITON "Tokenization failed\n"), 1);
		ft_expand(head, envt);
		cmd = ft_parser(head, &envt);
		ft_free_lst_token(head);
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
	return (0);
}
