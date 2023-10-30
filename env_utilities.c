/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:45:37 by theophane         #+#    #+#             */
/*   Updated: 2023/10/30 20:31:41 by mabimich         ###   ########.fr       */
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

void	env_i_setup(t_env **envt)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!(*envt))
		ft_key_add(envt, "PWD", pwd);
	free(pwd);
	shlvl_inc(envt);
	return ;
}
