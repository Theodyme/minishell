/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:12 by flplace           #+#    #+#             */
/*   Updated: 2023/03/22 17:55:02 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int chdir(const char *path);
// char *getcwd(char *buf, size_t size);

// 		int		ft_find_home()

int	ft_bltin_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*buf;
	int		i;
	t_env	*parse;

	i = 9;
	oldpwd = NULL;
	parse = NULL;
	if (ft_array_cntr(cmd->args) != 1)
		return (1);
	if (chdir(cmd->args[0]) == -1)
		return (1);
	parse = ft_key_finder(&cmd->envt, "PWD");
	oldpwd = (char *)malloc(sizeof(char) * (ft_strlen(parse->value) + 1));
	buf = (char *)malloc(sizeof(char) * (ft_strlen(parse->value) + ft_strlen(cmd->args[0]) + 1));
	ft_strcpy(oldpwd, parse->value);
	buf = getcwd(buf, (ft_strlen(parse->value) + ft_strlen(cmd->args[0])));
	printf("inside cd: buf = %s, i = %d\n", buf, i);
	ft_strcpy(parse->value, buf);
	return (0);
}
