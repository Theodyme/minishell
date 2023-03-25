/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:45:48 by flplace           #+#    #+#             */
/*   Updated: 2023/03/24 11:42:41 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_key_freer(char *key, char *value)
{
		free(key);
		free(value);
		return (0);
}

int		ft_array_cntr(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/* ------------ t_env	*ft_key_finder(t_env **envt, char *needle) ------------ */
/*
**		parcourt la liste chainee envt et cherche needle.
**
**		s'il la trouve, il renvoit l'adresse du node designe.
**		sinon, il renvoie NULL.
*/

t_env	*ft_key_finder(t_env **envt, char *needle)
{
	t_env	*parse;

	parse = (*envt);
	// printf("looking for %s key...\n", needle);
	while (parse->next)
	{
		// printf("comparing %s and %s...\n", parse->key, needle);
		if (ft_strcmp(parse->key, needle) == 0)
			break ;
		parse = parse->next;
	}
	if (ft_strcmp(parse->key, needle) != 0 && parse->next == NULL)
		return (NULL);
	// printf("found %s key! p = %p\n", parse->key, parse);
	return (parse);
}

/* ---------------------- int	ft_key_remove(t_env *rm) --------------------- */
/*
** 		free le node passe en parametre.
**
** 		verifie si le free s'est bien passe, sinon renvoie 1.
*/

int		ft_key_remove(t_env *rm)
{
	free(rm->key);
	free(rm->value);
	free(rm);
	rm = NULL;
	if (rm)
		return (1);
	return (0);
}

/* -------- t_env	*ft_key_add(t_env **envt, char *key, char *value) -------- */
/*
** 		ajoute une cle a la liste des var. environnement.
** 		la nouvelle cle respecte la syntaxe key=value selon les variables passees
**		en parametre. si la liste env est vide, ajoute la cle comme unique node.
**
** 		renvoie l'adresse du nouveau node ajoute.
*/

t_env		*ft_key_add(t_env **envt, char *key, char *value)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!(*envt))
	{
		*envt = new;
		return (new);
	}
	last = ft_envlast(*envt);
	last->next = new;
	return (new);
}
