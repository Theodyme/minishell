/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:49:22 by flplace           #+#    #+#             */
/*   Updated: 2023/09/02 17:07:07 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("        " GR """|''||''|               ||");
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

void	ft_setting_env(t_env *envt, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!envt)
		return ;
	tmp = cmd;
	while (tmp)
	{
		tmp->envt = envt;
		tmp = tmp->next;
	}
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
	g_status = 0;
	return (str);
}

void	shlvl_inc(t_env *envt)
{
	t_env	*shell;
	int		i;

	shell = ft_key_finder(&envt, "SHLVL");
	if (!shell)
	{
		write(2, "Error: Couldn't get shell lvl\n", 31);
		return ;
	}
	i = ft_atoi(shell->value);
	i++;
	free(shell->value);
	shell->value = ft_itoa(i);
	return ;
}

int		g_status = 0;

int	main(int ac, char **av, char **envp)
{
	int		debug = 0;
	char	*line = NULL;
	char	*status = NULL;
	t_env	*envt = NULL;
	t_cmd	*cmd = NULL;
	t_token	*head;

	ft_print_title1();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (ac != 1 && ac != 2)// && av)  attention a remettre a 1
		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
	if (ac == 2)
		debug = atoi(av[1]); // a enlever
	ft_env_reader(envp, &envt);
	if (!envt)
	{
		write(2, "Error: Couldn't get env variables\n", 34);
		return (1);
	}
	shlvl_inc(envt);
	g_status = 0;
	while (true)
	{
		status = return_status();
		line = readline(status);
		free(status);
		if (!line)
			break ;
		if (ft_count_quote(line) != -1) // penser a add history
			head = ft_tokenize(line);
		else
		{
			g_status = 2;
			write(2, "TRITONUnmatched quote\n", 23);
			continue ;
		}
		if (debug)
		{
			printf("Tokenization done\n");
			ft_print_token(head);
		}
		if (!head)
			return (write(2, "TRITONTokenization failed\n", 27), 1);
		ft_expand(head, envt);
		if (debug)
		{
			printf("\nExpansion done\n");
			ft_print_token(head);
		}
		cmd = ft_parser(head, envt);
		ft_free_lst_token(head);
		ft_setting_env(envt, cmd);
		if (debug)
		{
			printf("Parsing done\n");
			ft_print_cmd(cmd);
		}
		signal(SIGINT, SIG_IGN);
		ft_exec(cmd);
		//fprintf(stderr, "[%d]\n", g_status);
		signal(SIGINT, sig_handler);
		ft_add_history(line);
		// ft_free_lst_token(head);
		if (cmd)
			ft_free_cmd(&cmd);// ne semble pas supprimer pas envt de la commande
	}
	ft_clear_env(envt);
	if (cmd)
		ft_free_cmd(&cmd);
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	int 	debug = 0;
// 	char	*line = NULL;
// 	char*	status = NULL;
// 	t_env	*envt = NULL;
// 	t_cmd	*cmd = NULL;

// 	t_token	*head = NULL;

// 	ft_print_title();

// 	///////////////////////////////////////////// TESTING ARGS

// 	if (ac != 1 && ac != 2)// && av)  attention a remettre a 1
// 		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
// 	if (ac == 2)
// 		debug = atoi(av[1]); // a enlever
// 	ft_env_reader(envp, &envt);
// 	if (!envt) //voir si on peut mettre ca dans ft_env_reader
// 	{
// 		write(2, "Error: Couldn't get env variables\n", 34);
// 		return 1;
// 	}

// 	/////////////////////////////////////////////

// 	shlvl_inc(envt); // voir si on peut mettre ca dans ft_env_reader

// 	//////////////////////// PROCESS SPLIT
// 	while (true)
// 	{
// 		// printf("is heredoc donne AU DEBUT : %d\n", is_heredoc(head));
// 		status = return_status();
// 		line = readline(status);
// 		free(status);
// 		g_status = 0;
// 		if (!line)
// 			break ; // verifier que ca free ce qu il faut a la fois si c est la premiere ligne et pas la premiere

// 		// if (head && is_delimiter(head))
// 		// 	printf("is_delimiter donne : %s\n", is_delimiter(head)->str);
// 		// if (head && is_delimiter(head) && is_delimiter(head)->str)
// 		// {
// 		// 	if (!ft_strcmp(line, (is_delimiter(head))->str))
// 		// 	{
// 		// 		printf("testing heredocs : found delimiter here!\n");
// 		// 		free((is_delimiter(head))->str);
// 		// 		ft_argslist_to_array((!ft_strcmp(line, (is_delimiter(head))->str)));
// 		// 		ft_print_cmdlist(cmd->args_list);
// 		// 	}
// 		// 	else
// 		// 	{
// 		// 		ft_heredoc_cat(line, head, cmd);
// 		// 		printf("///////////////// HEREDOC CONCAT adding ''%s''\n", line);
// 		// 		ft_print_cmdlist(cmd->args_list);
// 		// 	}
// 		// }
// 		// else
// 		// {
// 			printf("///////////////// ELSE\n");
// 			if (ft_count_quote(line) != -1) // penser a add history
// 				head = ft_tokenize(line);
// 			else
// 			{
// 				write(2, "TRITONUnmatched quote\n", 23);
// 				continue ;
// 			}
// 			if (debug)
// 			{
// 				printf("Tokenization done\n");
// 				ft_print_token(head);
// 			}
// 			if (!head)
// 				return (write(2, "TRITONTokenization failed\n", 27), 1);
// 			ft_expand(head, envt);
// 			if (debug)
// 			{
// 				printf("Expansion done\n");
// 				ft_print_token(head);
// 			}
// 			cmd = ft_parser(head, envt);
// 		// }
// 		// printf("///////////////// BEFORE EXEC\n");
// 		////////////// CHECK IF tkn->DELIMITER->str exists
// 		// IF HEREDOC :		skip exec, skip the free part
// 		// and then :		read + check if line == DELIMITER, if not, add line to heredoc->str and skip again
// 		// 														else, replace DELIMITER->str
// 		//					then, in the exec, if tkn->HEREDOC->str != NULL, add it to argv, then exec
// 		// if (head && !is_delimiter(head))
// 		// {
// 			printf("///////////////// EXEC\n");
// 			ft_free_lst_token(head);
// 			ft_setting_env(envt, cmd);
// 			if (debug)
// 			{
// 				printf("Parsing done\n");
// 				ft_print_cmd(cmd);
// 			}
// 			ft_exec(cmd);
// 			ft_add_history(line);
// 			// ft_free_lst_token(head);
// 			if (cmd)
// 				ft_free_cmd(cmd);
// 		// }
// 	}

// 	////////////////////////////////////////////////
// 	ft_clear_env(envt);
// 	if (cmd)
// 		ft_free_cmd(cmd);
// 	return (0);
// }
