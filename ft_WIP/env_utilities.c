/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:45:37 by theophane         #+#    #+#             */
/*   Updated: 2023/08/04 15:05:06 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_env(t_env *envt)
{
	if (envt == NULL)
		return ;
	ft_clear_env(envt->next);
    free(envt->key);
    free(envt->value);
	envt->key = NULL;
	envt->value = NULL;
	envt->next = NULL;
	free(envt);
	envt = NULL;
	return ;
}
