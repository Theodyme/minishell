/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:29:41 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/30 17:29:45 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	void	*new_s;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	new_s = (char *)ft_calloc((len1 + len2 + 1), sizeof(char));
	if (new_s == NULL)
		return (NULL);
	ft_memmove(new_s, s1, ft_strlen(s1));
	ft_memmove(new_s + len1, s2, ft_strlen(s2));
	((char *)new_s)[len1 + len2] = '\0';
	return ((char *)new_s);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_s;

	new_s = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new_s);
}
