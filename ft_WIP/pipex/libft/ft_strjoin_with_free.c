/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:35:26 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/13 18:02:59 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_2strjoin_with_free(char *s1, char *s2, size_t val)
{
	void	*new_s;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_s = (char *)ft_calloc((len1 + len2 + 1), sizeof(char));
	if (new_s == NULL)
		return (NULL);
	ft_memmove(new_s, s1, ft_strlen(s1));
	ft_memmove(new_s + len1, s2, ft_strlen(s2));
	((char *)new_s)[len1 + len2] = '\0';
	val = val % 100;
	if (val % 100 / 10 && s1)
		free(s1);
	if (val % 10 && s2)
		free(s2);
	return ((char *)new_s);
}

char	*ft_3strjoin_with_free(char *s1, char *s2, char *s3, size_t val)
{
	void	*new_s;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (s1 == NULL && s2 == NULL && s3 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	new_s = (char *)ft_calloc((len1 + len2 + len3 + 1), sizeof(char));
	if (new_s == NULL)
		return (NULL);
	ft_memmove(new_s, s1, ft_strlen(s1));
	ft_memmove(new_s + len1, s2, ft_strlen(s2));
	ft_memmove(new_s + len1 + len2, s3, ft_strlen(s3));
	((char *)new_s)[len1 + len2 + len3] = '\0';
	val = val % 1000;
	if (val % 1000 / 100 && s1)
		free(s1);
	if (val % 100 / 10 && s2)
		free(s2);
	if (val % 10 && s3)
		free(s3);
	return ((char *)new_s);
}
