#include "../minishell.h"

void	free_tab_with_1blank(char **tab, char *str)
{
	size_t	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
	if (str)
		free(str);
}