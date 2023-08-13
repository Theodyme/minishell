/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theophane <theophane@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:42:26 by flplace           #+#    #+#             */
/*   Updated: 2023/08/13 20:02:40 by theophane        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_atoi(const char *str)
// {
// 	int	i;
// 	int	res;
// 	int	minus;

// 	minus = 1;
// 	i = 0;
// 	res = 0;
// 	while (ft_isspace(str[i]))
// 		i++;
// 	if (str[i] == 45 || str[i] == 43)
// 	{
// 		if (str[i] == 45)
// 			minus = -1;
// 		i++;
// 	}
// 	while (ft_isdigit(str[i]))
// 	{
// 		res = res * 10 + (str[i] - 48);
// 		i++;
// 	}
// 	return (res * minus);
// }

int    ft_atoi(const char *str)
{
    int            i;
    size_t        r;
    int            m;

    i = 0;
    r = 0;
    m = 1;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == '-' || str[i] == '+')
        if (str[i++] == '-')
            m = -1;
    while (ft_isdigit((int)str[i]))
    {
        if ((r * 10) + sizeof(char) > LONG_MAX)
        {
            if (m > 0)
                return (-1);
            else
                return (0);
        }
        r = r * 10 + str[i++] - '0';
    }
    return ((m * r));
}