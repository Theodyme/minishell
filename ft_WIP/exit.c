/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:57:43 by mabimich          #+#    #+#             */
/*   Updated: 2023/08/13 20:30:20 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_msg : affiche un message d'erreur
** @s1 : message d'erreur
** @s2 : message d'erreur
*/

void	ft_free_n_exit(t_cmd *cmd, int code)
{
	if (cmd->envt)
		ft_clear_env(cmd->envt);
	if (cmd && cmd->head)
	{
		cmd = cmd->head;
		ft_free_cmd(cmd);
	}
	else if (cmd)
		ft_free_cmd(cmd);
	exit(code);
}

void	ft_msg(char *s1, char *s2)
{
	char	*tmp;
	char	*out;

	tmp = ft_3strjoin_with_free("\033[34mᴛʀɪᴛoɴ\033[0m: ", s1, ": ", 0);
	if (!tmp)
		return ;
	out = ft_3strjoin_with_free(tmp, s2, "\n", 100);
	ft_putstr_fd(out, 2);
	free(out);
}

/*
** dispatch_exit2 : libère la mémoire, quitte le programme et renvoie un code
** @data : structure de données
** @code : code d'erreur
** @status : status de la commande
**
** Cette fonction libère la mémoire et quitte le programme.
** Elle est appelée par dispatch_exit.
** Elle gère les tout les codes et plus finement les codes d'erreurs suivants:
** 9 : builtin exit
** 8 : probleme lors de la creation d'un fork
** 7 : probleme lors de la creation du premier pipe
** 3 : probleme lors de l'allocation du tableau de path
** 2 : probleme lors de l'allocation du tableau de pid
** 1 : probleme lors de l'allocation de la structure de données
*/

void	dispatch_exit2(t_cmd *cmd, int code)
{


	// if (code > 6 && cmd->fd[1] != -1) //peut etre inversé
	// 	close(cmd->fd[1]);
	// if (code > 5 && cmd->fd[0] != -1)
	// 	close(cmd->fd[0]);
	// if (code > 3)
	// 	ft_free_tab_str(data->path, data->n_child);
	// if (code > 2)
	// 	free(cmd->pid);
	// if (code > 1)
	// 	free(cmd);
	// data = NULL;
	// cmd = NULL;
	// close(0);
	// close(1);
	// close(2);
	if (code == 21)
		write(2, "________NO_COMMAND________\n", 27);
	if (code == 126 || code == 127)
		ft_free_n_exit(cmd, code);
	if (code == 666 || code == 555)
		ft_free_n_exit(cmd, 1);
	if (code == 21 || code == 9)
		ft_free_n_exit(cmd, 0);
	//exit(WEXITSTATUS(1));
}

/*
** dispatch_exit : libère la mémoire, quitte le programme et renvoie un code
** @data : structure de données
** @code : code d'erreur
**
** Elle fait passer le code d'erreur à 7 si le premier pipe n'a pas pu être créé.
** Elle supprime le fichier temporaire du here_doc si il existe.
** Elle gere les codes d'erreurs suivants :
** i * 10 : Le pipe n°i n'a pas pu être créé, on ferme les pipes précédents
** 555 : Le fichier d'entrée n'a pas pu être ouvert
** 666 : Le fichier de sortie n'a pas pu être ouvert
** 777 : Aucun problème, on ferme tous les pipes et on attend les fils
** 127 : probleme lors de l'execution d'un processus fils
** On appelle dispatch_exit2 pour gerer les autres codes d'erreurs.
*/

void	dispatch_exit(t_cmd *cmd, int code)
{
	if (code == 0)
		code = 7;
	// if (code >= 10 && !(code % 10))
	// 	close_pipes2(cmd, 0);
	// if (cmd->hd_file && waitpid(cmd->pid, NULL, 0))
	// 	unlink(cmd->hd_file);
	// if (data->hd_file)
	// 	free(data->hd_file);
	// if (code == 777)
	// 	sleep(20);
	// fprintf(stderr,"_DISPATCH_EXIT_\n");
	// fprintf(stderr,"_code = %d\n", code);
	// if (cmd && cmd->name)
	// 	fprintf(stderr,"_cmd->pid = %s\n", cmd->name);
	// else
	// 	fprintf(stderr,"NO_NAME\n");
	// if (getpid())
	// 	fprintf(stderr,"_cmd->pid = %d\n", getpid());
	//printf address cmd:
	//fprintf(stderr,"__cmd = %s\n", cmd->name);
	if (!(code % 111))
	{
		close_pipes(cmd);
		while (code == 777 && cmd && cmd->pid != -1)
		{
			if (cmd->pid != -1 && cmd->pid != 1)
				waitpid(cmd->pid, &g_status, 0); // Il faut check qu'on attend pas que le dernier, mais tous a partir du 0 et pensez a ce qu il se passe si on ctrl c pendant le process d attente des enfants
			else if (cmd->pid == 1)
				g_status = cmd->status;
			cmd = cmd->next;
		}
	}
	if (code == 555)
	{
		close_pipes(cmd);
		if (cmd->fd[1])
			close(cmd->fd[1]);
		ft_msg(strerror(errno), cmd->name_file[0]);
		// ft_free_n_exit(cmd, 1);
	}
	if (code == 666)
	{
		close_pipes(cmd);
		if (cmd->fd[0])
			close(cmd->fd[0]);
		ft_msg(strerror(errno), cmd->name_file[1]);
		// ft_free_n_exit(cmd, 1);
	}
	dispatch_exit2(cmd, code);
}
