/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:13:33 by flplace           #+#    #+#             */
/*   Updated: 2023/03/15 16:43:02 by flplace          ###   ########.fr       */
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
** 		si export est tout seul, trie par ordre alphabetique?
** 		controle que la copie s'est bien passee, sinon retourne 1.
*/

int		ft_bltin_export(t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*needle;
	char	*key;
	char	*value;

	if (ft_array_cntr(cmd->args) != 1)
		return (1);
	key = ft_split_key(cmd->args[0]);
	value = ft_split_value(cmd->args[0]);
	needle = ft_key_finder(&(cmd->envt), key);
	if (!needle)
	{
		tmp = ft_key_add(&(cmd->envt), key, value);
		if (tmp && ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value) == 0)
		{
			ft_key_freer(key, value);
			return (0);
		}
	}
	else if (needle && (ft_strcmp(needle->value, value) != 0))
	{
		free(needle->value); // OR SOMETHING LIKE THAT, NEEDS TO CHECK THE LEAKS
		needle->value = value;
	}
	ft_key_freer(key, value);
	return (1);
}
