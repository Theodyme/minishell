/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:12 by flplace           #+#    #+#             */
/*   Updated: 2023/04/17 17:14:20 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int		ft_pwd_changer(t_cmd *cmd, char *path)
{
	t_env	*pwd = NULL;
	t_env	*oldpwd = NULL;

	oldpwd = ft_key_finder(&(cmd->envt), "OLDPWD");
	if (oldpwd == NULL)
		return (1);
	pwd = ft_key_finder(&cmd->envt, "PWD");
	if (pwd == NULL)
		return (1);
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = ft_strdup(path);
	printf("old pwd = %s\n", oldpwd->value);
	printf("current pwd = %s\n", pwd->value);
	return (0);
}

int		ft_home_finder(t_cmd *cmd, char *username)
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
	if (chdir(to_access) == -1)
	{
		free(path);
		free(to_access);
		printf("error: couldn't find home.\n");
		return (1);
	}
	return (0);
}

int		ft_path_changer(t_cmd *cmd)
{
	char	*path;
	t_env	*pwd = NULL;

	pwd = ft_key_finder(&cmd->envt, "PWD");
	if (pwd == NULL)
		return (1);
	if (cmd->argv[1][0] != '/')
		path = ft_pathbuilder(pwd->value, cmd->argv[1]);
	else
		path = ft_strdup(cmd->argv[1]);
	if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", cmd->argv[1]);
		free(path);
		return (1);
	}
	if (ft_pwd_changer(cmd, path) == 1)
		return (1);
	free(path);
	return (0);
}

int		ft_bltin_cd(t_cmd *cmd)
{
	if (ft_array_cntr(cmd->argv) > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (ft_array_cntr(cmd->argv) == 1)
	{
		ft_path_changer
	}
	if ((ft_array_cntr(cmd->argv) == 2) && (cmd->argv[1][0] == '~'))
	{
		ft_home_finder(cmd, (cmd->argv[1] + 1));
		return (1);
	}
	if (ft_path_changer(cmd) == 1)
		return (1);
	return (0);
}
