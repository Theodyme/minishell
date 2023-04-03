/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:13:45 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/17 20:40:18 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putendl_fd(char const *s, int fd)
{
	if (s && fd)
	{
		ft_putstr_fd((char *)s, fd);
		write(fd, "\n", 1);
	}
}
