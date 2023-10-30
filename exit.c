/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:57:43 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/30 21:31:26 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear_and_exit(t_cmd *cmd, t_env *envt)
{
	ft_clear_env(envt);
	if (cmd)
		ft_free_cmd(&cmd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (0);
}

void	ft_free_n_exit(t_cmd *cmd, int code)
{
	ft_clear_env(*cmd->envt);
	if (cmd && cmd->head)
	{
		cmd = cmd->head;
		ft_free_cmd(&cmd);
	}
	else if (cmd)
		ft_free_cmd(&cmd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(code);
}

/*
** ft_msg : affiche un message d'erreur
** @s1 : message d'erreur
** @s2 : message d'erreur
*/

void	ft_msg(char *s1, char *s2)
{
	char	*tmp;
	char	*out;

	tmp = ft_3strjoin_with_free(TRITON, s1, ": ", 0);
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
	int	tmp;

	tmp = g_status;
	if (WIFEXITED(tmp))
		g_status = WEXITSTATUS(tmp);
	else if (WIFSIGNALED(tmp))
	{
		g_status = 128 + WTERMSIG(tmp);
		if (g_status == 130)
			write(2, "\n", 1);
		if (g_status == 131)
			write(2, "Quit (core dumped)\n", 19);
	}
	// if (code == 21)
	// 	close(cmd->fd[0]);
	if (code == 126 || code == 127)
	{
		close_pipes(cmd);
		ft_free_n_exit(cmd, code);
	}
	if (code == 666 || code == 555)
		ft_free_n_exit(cmd, 1);
	if (code == 21 || code == 9)
	{
		close_pipes(cmd);
		ft_free_n_exit(cmd, 0);
	}
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
** 777 : Aucun problème, on ferme tous les pipes et on attend les fils
** 127 : probleme lors de l'execution d'un processus fils
** On appelle dispatch_exit2 pour gerer les autres codes d'erreurs.
*/

void	dispatch_exit(t_cmd *cmd, int code)
{
	if (cmd->bltn && !cmd->pid)
		ft_free_n_exit(cmd, code);
	else if (cmd->bltn && cmd->pid == 1)
		return ;
	if (code == 777)
	{
		close_pipes(cmd);
		if (cmd && !cmd->name && cmd->redir && cmd->redir->type != HEREDOC)
			return ;
		while (cmd && cmd->pid != -1)
		{
			if (cmd->pid != -1 && cmd->pid != 1)
				waitpid(cmd->pid, &g_status, 0);
			cmd = cmd->next;
		}
	}
	if (code == 130)
		ft_free_n_exit(cmd, code);
	dispatch_exit2(cmd, code);
}
