/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:55:51 by flplace           #+#    #+#             */
/*   Updated: 2023/08/14 18:59:25 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_hello(void)
{
	printf("\n⠀⠀⢠⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⡄\n");
	printf("⠀⠀⢸⠀" GR "⢀⠀⠀⠀⠀⢀⠀⡀⠀⠀⠀⠀⠀" WH "⠇");
	printf(BL "⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" WH "\n");
	printf("⠀⠀⢸⠀" GR "⢸⢢⠀⡶⠀⢸⠀⠇⠀⠖⡄⠸⠀" WH "⠇");
	printf(BL "⠀⠀⠀⣿⣷⣶⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" WH "\n");
	printf("⠀⠀⢸⠀" GR "⠈⠈⠀⠉⠀⠉⠀⠉⠀⠉⠀⠈" WH "⣀⣀⣳⠀");
	printf(BL "⠀⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀" WH "\n");
	printf("⠀⠀⠈⠳⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠞⠁⠀⠀⠀⠀" BL "⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡀⣀⣀⣠⣤⣴⣾⣿⡟⠀⠀⠀⠀⠀⠀" WH "\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" BL "⠈⠻⢿⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀" WH "\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" BL "⠀⢤⣤⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀" WH "\n");
	printf(BL "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⣀⣀⣀⢀⠀⢀⣀⡰⠃⠀⠀⠈⠉⠛⠿⠿⢿⢿⡿⠿⠛⠀⠀⠀⠀⠈⠉⠙⠛⠒⠶⠤⠤⠀⠀⠀" WH "\n");
	printf(BL "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀ ⠀⠈⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" WH "\n\n");
}

int	ft_bltin_hello(t_cmd *cmd)
{
	struct s_arg	*tmp;

	if (!cmd->args_list->next->str)
	{
		printf(TRITON "Who are you talking to?\n");
		return (1);
	}
	tmp = cmd->args_list->next;
	if (ft_strcmp(ft_str_tolower(tmp->str), "triton") != 0
		&& ft_strcmp(ft_str_tolower(tmp->str), "triton!") != 0)
		printf(TRITON "Who are you talking to?\n");
	else
		ft_print_hello();
	return (0);
}
