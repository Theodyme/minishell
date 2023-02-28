/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:13:33 by flplace           #+#    #+#             */
/*   Updated: 2023/02/24 12:10:47 by flplace          ###   ########.fr       */
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

int		ft_bltin_export(t_cmd_div *div, t_env **envt)
{
	t_env	*tmp;
	char	*key;
	char	*value;

	key = ft_split_key(div->args[1]);
	value = ft_split_value(div->args[1]);
	tmp = ft_key_add(envt, key, value);
	if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value) == 0)
		return (0);
	return (1);
}
