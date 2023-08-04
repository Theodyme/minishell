/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:55:53 by flplace           #+#    #+#             */
/*   Updated: 2023/08/04 14:32:39 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_currfile(char *path)
{
	int		i;

	i = ft_strchr_end(path, '/');
	if (i != -1)
	{
		return (path + i + 1);
	}
	return (NULL);
}

int	ft_bltin_where(t_cmd *cmd)
{
	struct s_arg	*tmp;
	struct s_env	*pwd;

	if (!cmd->args_list->next->str)
	{
		printf("\033[34mᴛʀɪᴛᴏɴ\033[0m: What do you mean?\n");
		return (1);
	}
	tmp = cmd->args_list->next;
	if (!tmp->next->str)
	{
		printf("\033[34mᴛʀɪᴛᴏɴ\033[0m: I don't get it.\n");
		return (1);
	}
	pwd = ft_key_finder(&(cmd->envt), "PWD");
	if (ft_strcmp(ft_str_tolower(tmp->str), "are") != 0
		&& ft_strcmp(ft_str_tolower(tmp->next->str), "we?") != 0
		&& ft_strcmp(ft_str_tolower(tmp->next->str), "we") != 0)
		printf("\033[34mᴛʀɪᴛᴏɴ\033[0m: Who are you talking to?\n");
	else
	{
		printf("\033[34mᴛʀɪᴛᴏɴ\033[0m: We're in the deep sea ! ");
		printf("Specifically in the %s Ocean.\n", ft_currfile(pwd->value));
	}
	return (0);
}
