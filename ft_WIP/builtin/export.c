/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:13:33 by flplace           #+#    #+#             */
/*   Updated: 2023/02/11 14:37:26 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//		int		ft_bltin_export(t_env **envt, char *key, char *value)
//
// 			apppelle ft_key_add() pour ajouter un nouveau node avec les
// 			valeurs passees en parametre.
//
// 			controle que la copie s'est bien passee, sinon retourne 1.

int		ft_bltin_export(t_env **envt, char *key, char *value)
{
	t_env	*tmp;

	tmp = ft_key_add(envt, key, value);
	if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value) == 0)
		return (0);
	return (1);
}
