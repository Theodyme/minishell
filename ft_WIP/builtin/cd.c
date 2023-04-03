/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:12 by flplace           #+#    #+#             */
/*   Updated: 2023/04/03 16:12:23 by mabimich         ###   ########.fr       */
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

int		ft_bltin_cd(t_cmd *cmd)
{
	char	*path;
	t_env	*pwd = NULL;

	if ((ft_array_cntr(cmd->argv) == 1) && (cmd->argv[0][0] == '~'))
	{
		ft_home_finder(cmd, (cmd->argv[0] + 1));
		return (1);
	}
	if (ft_array_cntr(cmd->argv) != 1)
		return (1);
	pwd = ft_key_finder(&cmd->envt, "PWD");
	if (pwd == NULL)
		return (1);
	path = ft_pathbuilder(pwd->value, cmd->argv[0]);
	if (chdir(path) == -1)
	{
		free(path);
		return (1);
	}
	if (ft_pwd_changer(cmd, path) == 1)
		return (1);
	free(path);
	return (0);
}
