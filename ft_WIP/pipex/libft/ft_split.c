/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:55:44 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/17 21:18:13 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freesplit(char **tab, int i)
{
	while (i >= 0)
		free(tab[i--]);
	free(tab);
}

static int	ft_count_word(const char *str, char c)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (str[i])
	{
		if ((!i && str[i] != c) || (str[i] != c && str[i - 1] == c))
			l++;
		i++;
	}
	return (l);
}

static char	*ft_alloc_word(char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = (char *)ft_calloc(sizeof(char), i + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**out;
	int		j;

	i = 0;
	j = 0;
	out = (char **)ft_calloc(sizeof(char *), ft_count_word(s, c) + 1);
	if (!out)
		return (NULL);
	while (s[i])
	{
		if ((!i && s[i] != c) || (s[i] != c && s[i - 1] == c))
		{
			out[j] = ft_alloc_word((char *) &s[i], c);
			if (!out[j])
			{
				ft_freesplit(out, j);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	out[j] = NULL;
	return (out);
}
