/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:41:16 by flplace           #+#    #+#             */
/*   Updated: 2023/03/15 16:37:43 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_bltin_pwd(t_cmd *cmd)
{
	t_env	*pwd;

	pwd = NULL;
	pwd = ft_key_finder(&(cmd->envt), "PWD");
	if (pwd == NULL)
		return (1);
	printf("%s\n", pwd->value);
	return (0);
}
