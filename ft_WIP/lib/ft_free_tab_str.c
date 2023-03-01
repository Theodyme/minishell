#include "../minishell.h"

void	ft_free_tab_str(char **tab, int max)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	if (max != -1)
		while (i < max)
			free(tab[i++]);
	else
		while (tab[i])
			free(tab[i++]);
	free(tab);
}
