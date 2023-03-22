#include "minishell.h"

void ft_add_history(char *line)
{
	if (line && *line)
		add_history(line);
	if (line)
	{
		free(line);
		line = NULL;
	}
	return;
}

int in_quote(char **ptr1, char **ptr2)
{
	if (ptr1 == NULL || ptr2 == NULL || **ptr1 == '\0' || **ptr2 == '\0')
		return (0);
	*ptr2 = *ptr2 + 1;
	if (**ptr1 != '\'' && **ptr1 != '\"')
	{
		*ptr1 = *ptr1 + 1;
		return (0);
	}
	else
	{
		if (**ptr1 == **ptr2)
			return (*ptr1 = ++(*ptr2), 0);
		else if (**ptr1 == '\'')
			return (1);
		else if(**ptr1 == '\"')
			return (2);
	}
	return (0);
}

/*

char *ft_expand_old(char *line)
{
	//	char	*tmp;
	char *ptr1;
	char *ptr2;
	// int		i;

	//	tmp = NULL;
	ptr1 = line;
	ptr2 = line;
	while (ptr2 && *ptr2)
	{
		// printf("%c\n", *ptr1);
		// forward(&ptr1);
		// printf("%c\n", *ptr1);

		//		printf("%c|%c\n", *ptr1, *ptr2);
		//		printf("%c|%c\n", *ptr1, *ptr2);
		printf("%c|%c|%i\n", *ptr1, *ptr2, in_quote(&ptr1, &ptr2) );
		//in_quote(ptr1, ptr2);
	}
	return (line);
}
*/
