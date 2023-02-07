/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:50:46 by mabimich          #+#    #+#             */
/*   Updated: 2023/02/07 12:49:20 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_quote(char *str)
{
	int		i;
	int		v;
	char	c;

	i = -1;
	v = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
				v++;
			else
				return (-1);
		}
	}
	return (v);
}

int	ft_quotelen(char *str)
{
	int		i;
	int		v;
	char	c;

	i = -1;
	v = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
				v++;
			else
				return (-1);
		}
		else
			return (-1);
	}
	return (v);
}

// int ft_readlst(t_token *lst)
// {
// 	if (!lst)
// 		return (1);
// 	if (lst->str && lst->next)
// 		lst = lst->next;
// 	printf("lst->str:");
// 	while (lst)
// 	{
// 		printf("|%s|", lst->str);
// 		lst = lst->next;
// 	}
// 	printf("\n\n");
// 	return (0);
// }


/*

int main()
{
	//t_token *lst = NULL;

	//lst = ft_lstnew(ft_strdup(""));

	char *str = ft_strdup("'Hel'lo W\"orl'd");


	char *str1 = ft_strdup("hello world");
	char *str2 = ft_strdup("hel\'lo wor\'ld");
	char *str3 = ft_strdup("hel\"lo wor\"ld");
	char *str4 = ft_strdup("hel\'lo wor\"ld");
	char *str5 = ft_strdup("hel\"lo wor\'ld");
	char *str6 = ft_strdup("hel\'lo \'wor\'ld");
	char *str7 = ft_strdup("hel\"lo \"wor\"ld");
	char *str8 = ft_strdup("hel\'lo \"wor\'ld");
	char *str9 = ft_strdup("hel\"lo \'wor\"ld");
	char *str10 = ft_strdup("hel\'lo \'wor\"ld");
	char *str11 = ft_strdup("hel\"lo \"wor\'ld");
	char *str12 = ft_strdup("hello \'world");
	char *str13 = ft_strdup("hello \"world");
	char *str14 = ft_strdup("h\'el\'l\"o \'world\"");
	char *str15 = ft_strdup("h\"el\"l\'o \"world\'");

	printf("= %d\n", ft_count_quote(str));
	printf("= %d\n", ft_count_quote(str1));
	printf("= %d\n", ft_count_quote(str2));
	printf("= %d\n", ft_count_quote(str3));
	printf("= %d\n", ft_count_quote(str4));
	printf("= %d\n", ft_count_quote(str5));
	printf("= %d\n", ft_count_quote(str6));
	printf("= %d\n", ft_count_quote(str7));
	printf("= %d\n", ft_count_quote(str8));
	printf("= %d\n", ft_count_quote(str9));
	printf("= %d\n", ft_count_quote(str10));
	printf("= %d\n", ft_count_quote(str11));
	printf("= %d\n", ft_count_quote(str12));
	printf("= %d\n", ft_count_quote(str13));
	printf("= %d\n", ft_count_quote(str14));
	printf("= %d\n", ft_count_quote(str15));


	// if(ft_quote(str1, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	//  lst = ft_lstnew(ft_strdup(""));
	//  if(ft_quote(str2, lst))
	//  	printf("error\n");
	// else
	//  	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str3, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str4, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str5, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str6, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str7, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str8, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str9, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str10, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str11, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str12, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));
	// if(ft_quote(str13, lst))
	// 	printf("error\n");
	// else
	// 	ft_readlst(lst);
	// lst = ft_lstnew(ft_strdup(""));

	return 0;
}*/
