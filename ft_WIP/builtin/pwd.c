/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:04:30 by flplace           #+#    #+#             */
/*   Updated: 2023/02/11 11:56:40 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_bltin_pwd(t_env **envt)
{
	t_env	*pwd;

	pwd = NULL;
	pwd = ft_key_finder(envt, "PWD");
	printf("%s\n", pwd->value);
	return ;
}
