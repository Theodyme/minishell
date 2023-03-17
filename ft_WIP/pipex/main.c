/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:28:34 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/17 18:25:14 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** ft_dup : duplique les descripteurs de fichiers pour le processus enfant
** @data : structure contenant les données du programme
** @i : numéro du processus enfant
**
** Cette fonction utilise l'appel système dup2 pour dupliquer les descripteurs
** de fichiers appropriés pour chaque processus enfant.
** - Si i est égal à 0, cela signifie que c'est le premier processus enfant
** - Si i est égal à data->n_child - 1, signifie que c'est le dernier enfant
** - Dans tous les autres cas, c'est un processus enfant intermédiaire
** Pour chaque cas, on duplique le descripteur de fichier approprié pour
** l'entrée et la sortie standard.
*/

void	ft_dup(t_data *data, int i)
{
	if (i == 0)
	{
		if (data->file[0] == -1)
			dispatch_exit(data, 555);
		dup2(data->file[0], STDIN_FILENO);
		dup2(data->vanne[(i * 2) + 1], STDOUT_FILENO);
	}
	else if (i == data->n_child - 1)
	{
		if (data->file[1] == -1)
			dispatch_exit(data, 666);
		dup2(data->vanne[(i * 2) - 2], STDIN_FILENO);
		dup2(data->file[1], STDOUT_FILENO);
	}
	else
	{
		dup2(data->vanne[(i * 2) - 2], STDIN_FILENO);
		dup2(data->vanne[(i * 2) + 1], STDOUT_FILENO);
	}
}

/*
** Open files : ouvre les fichiers de redirection pour le processus parent
** @data : structure contenant les données du programme
**
** Cette fonction ouvre les fichiers de redirection pour le processus parent.
** On ouvre ensuite le fichier de redirection d'entrée et de sortie.
** Enfin, on ouvre les pipes pour les processus enfants.
*/

void	open_files(t_data *data)
{
	int	i;

	i = -1;
	data->file[0] = open(data->argv[1], O_RDONLY);
	data->file[1] = open(data->argv[data->n_child + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (i + 2 < data->n_child)
		if (pipe(&data->vanne[(++i) * 2]) == -1)
			dispatch_exit(data, 10 * i);
}

/*
** Child : fonction exécutée par chaque processus enfant
** @data : structure contenant les données du programme
** @i : numéro du processus enfant
** @envp : tableau de chaînes de caractères contenant les variables d'environnement
**
** Cette fonction est exécutée par chaque processus enfant.
** On duplique les descripteurs de fichiers pour le processus enfant avec ft_dup.
** On ferme ensuite les descripteurs de fichiers et les pipes inutiles.
** On sépare la commande en arguments avec ft_split.
** On exécute la commande avec execve.
** Si la commande n'est pas trouvée, elle affiche un message d'erreur.
** Enfin, elle appelle la fonction dispatch_exit pour quitter le programme.
** Le code de sortie est 127 si la commande n'est pas trouvée.
*/

void	child(t_data *data, char **envp, int i)
{
	char	**argv;

	ft_dup(data, i);
	if (data->file[0] != -1)
		close(data->file[0]);
	if (data->file[1] != -1)
		close(data->file[1]);
	close_pipes(data, -1);
	argv = ft_split(data->argv[i + 2], ' ');
	if (data->path[i] && argv)
		execve(data->path[i], argv, envp);
	ft_msg("Command not found", argv[0]);
	if (argv)
		ft_free_tab_str(argv, -1);
	dispatch_exit(data, 127);
}

/*
** init : initialise la structure data
** @argv : tableau de chaînes de caractères contenant les arguments du programme
** @envp : tableau de chaînes de caractères contenant les variables d'environnement
**
** Cette fonction initialise la structure data.
** Elle alloue de la mémoire pour la structure data, les tableaux de pid_t,
** les tableaux de chaînes de caractères contenant les chemins des commandes,
** et les tableaux de chaînes de caractères contenant les arguments des commandes.
** Finalement, elle retourne la structure data.
*/

t_data	*init(char **argv, char **envp)
{
	int		i;
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		dispatch_exit(data, 1);
	data->argv = argv;
	data->here_doc = 0;
	data->n_child = 2;
	data->pid = ft_calloc_full(sizeof(pid_t), data->n_child);
	if (!data->pid)
		dispatch_exit(data, 2);
	data->path = ft_calloc(sizeof(char **), data->n_child);
	if (!data->path)
		dispatch_exit(data, 3);
	i = -1;
	while (++i < data->n_child)
	{
		if (!argv[i + 2] || !argv[i + 2][0])
			continue ;
		data->path[i] = get_path(argv[i + 2], envp);
	}
	return (open_files(data), data);
}

/*
** Main : fonction principale du programme
** @ac : nombre d'arguments
** @av : tableau d'arguments
** @envp : tableau d'environnement
**
** Cette fonction est exécutée au lancement du programme.
** Elle vérifie le nombre d'arguments et appelle la fonction init.
** Puis pour chaque processus enfant, elle appelle la fonction fork.
** Si fork retourne -1, il s'agit d'une erreur et le programme s'arrête.
** Si fork retourne 0, il s'agit du processus enfant et on appelle la fonction child.
** Si fork retourne un pid, il s'agit du processus parent et on continue.
** Enfin, elle appelle la fonction dispatch_exit pour quitter le programme.
** Le code de sortie est 777 si tout s'est bien passé.
*/

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_data	*data;

	data = NULL;
zzz
	data = init(av, envp);
	i = 0;
	while (i < data->n_child && data->pid[i])
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			dispatch_exit(data, 8);
		if (!data->pid[i])
			child(data, envp, i);
		i++;
	}
	dispatch_exit(data, 777);
	return (0);
}
