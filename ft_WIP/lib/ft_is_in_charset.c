#include "../minishell.h"

int	ft_is_in_charset(const char c, const char *charset)
{
	int	i;

	i = 0;
	if (!charset)
		return (0);
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}
