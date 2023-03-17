/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:45:48 by flplace           #+#    #+#             */
/*   Updated: 2023/03/17 22:20:54 by mabimich         ###   ########.fr       */
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
	while (array)
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
	while (parse->next)
	{
		if (ft_strcmp(parse->key, needle) == 0)
			break ;
		parse = parse->next;
	}
	if (parse->next == NULL)
		return (NULL);
	return (parse);
}

char	*ft_key_finder2(t_env **envt, char *needle)
{
	t_env	*parse;

	parse = (*envt);
	while (parse->next)
	{
		if (ft_strcmp(parse->key, needle) == 0)
			break ;
		parse = parse->next;
	}
	if (parse->next == NULL)
		return (NULL);
	return (parse->value);
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
