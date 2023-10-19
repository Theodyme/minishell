/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:12 by flplace           #+#    #+#             */
/*   Updated: 2023/10/18 15:40:13 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pathbuilder(char *path, char *cmdname)
{
	char	*to_access;

	to_access = (char *)ft_calloc(sizeof(char), (ft_strlen(path)
				+ ft_strlen(cmdname) + 2));
	ft_strcat(to_access, path);
	ft_strcat(to_access, "/");
	ft_strcat(to_access, cmdname);
	return (to_access);
}

int	ft_pwd_changer(t_cmd *cmd)
{
	t_env	*pwd;
	t_env	*oldpwd;

	oldpwd = ft_key_finder(cmd->envt, "OLDPWD");
	if (oldpwd == NULL)
		return (1);
	pwd = ft_key_finder(cmd->envt, "PWD");
	if (pwd == NULL)
		return (1);
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = getcwd(NULL, 0);
	return (0);
}

int	ft_path_changer(t_cmd *cmd)
{
	char	*path;
	t_env	*pwd;

	pwd = ft_key_finder(cmd->envt, "PWD");
	if (pwd == NULL)
		return (1);
	if (cmd->argv[1][0] != '/' && cmd->argv[1][0] != '.')
		path = ft_pathbuilder(pwd->value, cmd->argv[1]);
	else
		path = ft_strdup(cmd->argv[1]);
	if (chdir(path) == -1)
	{
		printf(TRITON "cd: %s: No such file or directory\n",
			cmd->argv[1]);
		free(path);
		return (1);
	}
	if (ft_pwd_changer(cmd) == 1)
		return (1);
	free(path);
	return (0);
}

int	ft_pwd_finder(t_cmd *cmd, char *arg)
{
	t_env	*node;

	node = ft_key_finder(cmd->envt, arg);
	if (!(node) && (ft_strcmp(arg, "HOME") != 0))
		return (1);
	else if (!(node) && (ft_strcmp(arg, "HOME") == 0))
	{
			printf(TRITON "cd: HOME not set\n");
			return (1);
	}
	if (chdir(node->value) == -1)
	{
		printf(TRITON "cd: couldn't find %s directory\n", arg);
		return (1);
	}
	if (ft_pwd_changer(cmd) == 1)
		return (1);
	return (1);
}

int	ft_bltin_cd(t_cmd *cmd)
{
	if (cmd->next && cmd->next->name)
		return (1);
	if (ft_args_cntr(cmd->args_list) == 1)
	{
		if (ft_pwd_finder(cmd, "HOME") == 1)
			return (1);
	}
	else if (ft_args_cntr(cmd->args_list) > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else if (cmd->argv[1][0] == '-' && !(cmd->argv[1][1]))
	{
		if (ft_pwd_finder(cmd, "OLDPWD") == 1)
			return (1);
	}
	else if (ft_path_changer(cmd) == 1)
		return (1);
	return (0);
}
