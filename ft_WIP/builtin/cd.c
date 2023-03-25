/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:12 by flplace           #+#    #+#             */
/*   Updated: 2023/03/25 15:05:08 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int chdir(const char *path);
// char *getcwd(char *buf, size_t size);

// 		int		ft_find_home()

char	*ft_pathbuilder(char *path, char *cmdname)
{
	char	*to_access;

	to_access = (char *)ft_calloc(sizeof(char), (ft_strlen(path) + ft_strlen(cmdname) + 2));
	ft_strcat(to_access, path);
	ft_strcat(to_access, "/");
	ft_strcat(to_access, cmdname);
	return (to_access);
}

int	ft_home_finder(t_cmd *cmd, char *username)
{
	t_env	*home;
	int		userlen;
	char	*path;
	char	*to_access;
	int		i;

	i = 0;
	home = ft_key_finder(&(cmd->envt), "HOME");
	userlen = ft_strlen(ft_key_finder(&(cmd->envt), "USER")->value);
	path = ft_strndup(home->value, (ft_strlen(home->value) - (userlen + 1)));
	to_access = ft_pathbuilder(path, username);
	printf("moving to following home: %s\n", to_access);
	if (chdir(to_access) == -1)
	{
		free(path);
		free(to_access);
		printf("error: couldn't find home.\n");
		return (1);
	}
	return (0);
}

int	ft_bltin_cd(t_cmd *cmd)
{
	char	*path;
	t_env	*pwd;
	t_env	*oldpwd = NULL;

	if ((ft_array_cntr(cmd->args) == 1) && (cmd->args[0][0] == '~'))
	{
		ft_home_finder(cmd, (cmd->args[0] + 1));
		return (1);
	}
	if (ft_array_cntr(cmd->args) != 1)
		return (1);
	oldpwd = ft_key_finder(&(cmd->envt), "OLDPWD");
	printf("oldpwd = %s\n", oldpwd->value);
	if (oldpwd == NULL)
		return (1);
	pwd = ft_key_finder(&cmd->envt, "PWD");
	printf("pwd = %s\n", pwd->value);
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	path = ft_pathbuilder(pwd->value, cmd->args[0]);
	printf("pathbuilder = %s\n", path);
	if (chdir(path) == -1)
	{
		free(path);
		return (1);
	}
	free(pwd->value);
	pwd->value = ft_strdup(path);
	free(path);
	printf("old path = %s\n", oldpwd->value);
	printf("current path = %s\n", pwd->value);
	return (0);
}
