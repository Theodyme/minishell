/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:28:34 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/27 22:31:14 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Child : fonction exécutée par chaque processus enfant
** @cmd : structure contenant les données du programme
**
** Cette fonction est exécutée par chaque processus enfant.
** On duplique les descripteurs de fichiers pour le processus enfant avec ft_dup.
** On ferme ensuite les descripteurs de fichiers et les pipes inutiles.
** On sépare la commande en arguments avec ft_split.
** On exécute la commande avec execve.
** Si la commande n'est pas trouvée, elle affiche un message d'erreur.
** Enfin, elle appelle la fonction dispatch_exit pour quitter le programme.
** Le code de sortie est 127 si la commande n'est pas trouvée.
** Le code de sortie est 126 si la commande n'est pas exécutable.
** Le code de sortie est 126 si la commande est un répertoire.
** Le code de sortie est 21 si la commande est vide.
*/

void	child(t_cmd *cmd)
{
	char		*path;
	struct stat	st;

	if (!cmd->name)
		dispatch_exit(cmd, 21);
	init_child(cmd);
	path = get_path(cmd->name, cmd->envp);
	if (path && stat(path, &st) != -1 && (access(path, F_OK | X_OK)
			|| S_ISDIR(st.st_mode)))
	{
		if (S_ISDIR(st.st_mode))
			ft_msg(cmd->name, "is a directory");
		else
			ft_msg(cmd->name, "command found but not executable");
		free(path);
		dispatch_exit(cmd, 126);
	}
	if (path && cmd->argv && cmd->argv[0])
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->argv, cmd->envp);
	}
	ft_msg(cmd->name, "command not found");
	dispatch_exit(cmd, 127);
}

int	ft_exec(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		out;

	if (!cmd)
		return (1);
	tmp = cmd;
	open_pipes(tmp);
	while (tmp && tmp->pid)
	{
	//	out = 0;
		out = ft_bltin_tester(&tmp);
		if (out == 0)
			out = ft_fun_builder(&tmp);
		if (out == 0)
			tmp->pid = fork();
		if (out == 2 && !tmp->head->next)
			dispatch_exit(tmp, 9);
		if (tmp->pid == -1 && out != 1 && out != 2)
			dispatch_exit(tmp, 8);
		if (!tmp->pid)
			child(tmp);
		tmp = tmp->next;
	}
	dispatch_exit(cmd->head, 777);
	return (0);
}
