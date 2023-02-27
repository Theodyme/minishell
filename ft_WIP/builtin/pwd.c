/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:04:30 by flplace           #+#    #+#             */
/*   Updated: 2023/02/23 17:08:47 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_bltin_pwd(t_cmd_div *div)
{
	t_env	*pwd;

	pwd = NULL;
	pwd = ft_key_finder(&(div->envt), "PWD");
	printf("%s\n", pwd->value);
	return ;
}
