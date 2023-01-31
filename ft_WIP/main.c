#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main(int ac, char **av)
{
	char *line = NULL;
	t_token *head;

	if (ac != 1 && av)
		return (write(2, "Error: Wrong number of arguments\n", 33), 1);
	head = ft_calloc(1, sizeof(t_token));
	if (!head)
		return 1;
	while (true)
	{
		line = readline(ft_strdup("$> "));
		if (!line)
			break ;
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		if (ft_count_quote(line) != -1)
		{
			line = ft_expand(line);
			//ft_quote(line, head);
		}
		else
			write(1, "Error: Unmatched quote\n", 23);
		ft_add_history(line);

	}
	return 0;
}