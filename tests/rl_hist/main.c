#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	rl_gets(char *line);

int		main(int ac, char **av)
{
	static char *line = NULL;

	line = readline("");
	add_history(line);
	while (line != NULL)
	{
		rl_gets(line);
	}
	write_history(av[1]);
	return 1;
}
