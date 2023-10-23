/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:58:45 by flplace           #+#    #+#             */
/*   Updated: 2023/10/23 16:37:56 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_split_key(char *str)
{
	char	*key;

	key = ft_strndup(str, ft_strclen(str, '='));
	return (key);
}

char	*ft_split_value(char *str)
{
	char	*rawvalue;
	char	*value;

	str += ft_strclen(str, '=') + 1;
	rawvalue = ft_strdup(str);
	value = ft_strtrim_free(rawvalue, C_BLANK);
	return (value);
}

t_env	*ft_lstadd_env(char *str, t_env **envt)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = ft_split_key(str);
	new->value = ft_split_value(str);
	new->next = NULL;
	if (!(*envt))
	{
		*envt = new;
		return (new);
	}
	last = ft_envlast(*envt);
	last->next = new;
	return (new);
}

int	ft_env_reader(char **envp, t_env **envt)
{
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		ft_lstadd_env(envp[i], envt);
		if (ft_envlast(*envt) == NULL)
			return (1);
		i++;
	}
	return (0);
}
