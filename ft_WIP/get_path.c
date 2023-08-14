/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:35:18 by flplace           #+#    #+#             */
/*   Updated: 2023/08/14 18:20:10 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** verif_paths : vérifie si les chemins des commandes sont valides
** @paths : tableau de chemins
** @cmd : commande
**
** Cette fonction vérifie si les chemins des commandes sont valides.
** Elle retourne le chemin valide, ou NULL si aucun chemin n'est valide.
*/

char	*verif_paths(char **paths, char *cmd)
{
	int		i;
	char	*out;

	out = NULL;
	i = -1;
	if (!paths)
		return (printf("BLBLᴛʀɪᴛᴏɴ\033[0m\033[0m: path is NULL\n"),
			NULL);
	while (paths && paths[++i])
	{
		if (!access(paths[i], F_OK | X_OK) && !out)
			out = ft_strdup(paths[i]);
		free(paths[i]);
	}
	if (!out && !access(cmd, F_OK | X_OK))
		out = ft_strdup(cmd);
	if (paths)
		free(paths);
	return (out);
}

/*
** get_path : récupère le chemin d'une commande
** @cmd : commande
** @envp : tableau d'environnement
**
** Cette fonction récupère le chemin d'une commande.
** Elle retourne le chemin de la commande, ou NULL si le chemin n'est pas trouvé.
*/

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*tmp;

	i = -1;
	while (envp && envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	if (!envp || !envp[i] || ft_strncmp(envp[i], "PATH=", 5))
		return (NULL);
	tmp = ft_pick(envp[i], '=', 1);
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	free(tmp);
	i = -1;
	while (paths && paths[++i])
	{
		paths[i] = ft_3strjoin_with_free(paths[i], "/", cmd, 100);
		if (!paths[i])
			free_tab_with_1blank(paths);
	}
	return (verif_paths(paths, cmd));
}
