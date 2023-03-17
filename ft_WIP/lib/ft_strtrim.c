#include "../minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	char	*new_s;
	int		l;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	l = ft_strlen(s1) + 1;
	while (--l && ft_is_in_charset(s1[start], set))
		start++;
	while (l && ft_is_in_charset(s1[start + l - 1], set))
		l--;
	new_s = ft_substr(s1, start, l);
	if (!new_s)
		return (NULL);
	return (new_s[l] = '\0', new_s);
}

char	*ft_strtrim_free(char *s1, char const *set)
{
	char	*new_s;

	new_s = ft_strtrim(s1, set);
	free(s1);
	return (new_s);
}