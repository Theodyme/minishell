/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:47:41 by mabimich          #+#    #+#             */
/*   Updated: 2022/05/31 19:03:32 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strclen_gnl(const char *str, int len, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (i < (len - 0) && str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = ft_strclen_gnl((char *)s2, BUFFER_SIZE, '\0');
	new_s = malloc((i + j + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}	
	while (s2 && s2[j] && j < BUFFER_SIZE)
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}

char	*get_line(char *tab, size_t fd)
{
	char	*line;
	size_t	ret;
	char	*box;

	line = NULL;
	ret = 0;
	if (tab[0])
		line = ft_strjoin_gnl(line, tab);
	while (ft_strclen_gnl(tab, BUFFER_SIZE, '\n') == -1)
	{
		ret = read(fd, tab, BUFFER_SIZE);
		if (!ret)
			return (tab[0] = 0, line);
		if (ret < BUFFER_SIZE)
			tab[ret] = 0;
		box = line;
		line = ft_strjoin_gnl(line, tab);
		free(box);
	}
	ret = 0;
	while (line && line[ret++])
		if (line[ret] && line[ret - 1] == '\n')
			line[ret] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	tab[128][BUFFER_SIZE];
	char		*str;
	int			i;
	int			j;

	str = NULL;
	j = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, str, 0) < 0)
		return (NULL);
	str = get_line(tab[fd], fd);
	i = ft_strclen_gnl(tab[fd], BUFFER_SIZE, '\n') + 1;
	while (i && i < BUFFER_SIZE)
		tab[fd][j++] = tab[fd][i++];
	if (j < BUFFER_SIZE)
		tab[fd][j] = 0;
	return (str);
}
