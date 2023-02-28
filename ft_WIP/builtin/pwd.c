/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:41:16 by flplace           #+#    #+#             */
/*   Updated: 2023/02/28 17:03:15 by mabimich         ###   ########.fr       */
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
