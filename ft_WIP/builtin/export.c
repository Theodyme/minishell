/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:13:33 by flplace           #+#    #+#             */
/*   Updated: 2023/03/24 11:56:11 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ------- int	ft_bltin_export(t_env **envt, char *key, char *value) ------- */
/*
** 		appelle ft_key_add() pour ajouter un nouveau node avec les valeurs
**		passees en parametre.
**
** 		print export ?
** 		si ca existe, modifier
** 		si export est tout seul, trie par ordre C_ALPHAbetique?
** 		controle que la copie s'est bien passee, sinon retourne 1.
*/

int		ft_bltin_export(t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*needle = NULL;
	char	*key = NULL;
	char	*value = NULL;

	if (ft_array_cntr(cmd->args) != 1)
		return (1);
	key = ft_split_key(cmd->args[0]);
	value = ft_split_value(cmd->args[0]);
	needle = ft_key_finder(&(cmd->envt), key);
	// printf("needle = %p\n", ft_key_finder(&(cmd->envt), key));
	// if (needle != NULL)
		// printf("found %s : strcmp result = %d\n", needle->key, ft_strcmp(needle->value, value));
	if (!needle)
	{
		tmp = ft_key_add(&(cmd->envt), key, value);
		if (tmp && ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value) == 0)
		{
			// printf("we just printed %s (key) and %s (value) in node %p\n", tmp->key, tmp->value, tmp);
			ft_key_freer(key, value);
			return (0);
		}
	}
	if (needle != NULL && (ft_strcmp(needle->value, value) != 0))
	{
		// printf("needle should replace actual value\n");
		free(needle->value); // OR SOMETHING LIKE THAT, NEEDS TO CHECK THE LEAKS
		needle->value = ft_strdup(value);
	}
	ft_key_freer(key, value);
	return (1);
}
