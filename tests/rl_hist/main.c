#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	rl_gets(char *line);

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		main(int ac, char **av)
{
	static char *line = NULL;

	line = readline("");
	add_history(line);
	while (line != NULL)
	{
		rl_gets(line);
		if (ft_strcmp(line, "exit") == 0)
			break ;
	}
	write_history(av[1]);
	return 1;
}
