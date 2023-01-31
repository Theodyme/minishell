/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:50:46 by mabimich          #+#    #+#             */
/*   Updated: 2023/01/04 16:50:52 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cc;

	if (!b)
		return (NULL);
	cc = (unsigned char *)b;
	while (len--)
		cc[len] = (unsigned char)c;
	b = (void *)cc;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	int	*tab;

	tab = (void *)malloc(size * count);
	if (!tab)
		return (NULL);
	ft_memset(tab, 0, size * count);
	return (tab);
}

size_t	ft_strlen(const char *str)
{
	int	l;

	l = 0;
	while (str && str[l] != '\0')
		l++;
	return (l);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = -1;
	if (!(size))
		return (ft_strlen(src));
	while (src[++i] && size > i + 1)
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

char	*ft_strldup(const char *src, size_t len)
{
	int		l;
	char	*str;

	if (src == NULL)
		return (NULL);
	l = ft_strlen((char *)src);
	str = (char *)ft_calloc(sizeof(*str), (l + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, src, len);
	return (str);
}



void	ft_lstadd_back(t_token **alst, t_token *new)
{
	t_token	*lt;

	if (!new || !alst)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	lt = ft_lstlast(*alst);
	lt->next = new;
}

t_token	*ft_lstnew(void *str)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->str = str;
	return (new);
}


char	*ft_strcpy(char *dest, const char *src)
{
	int		i;

	i = 0;
	if (src == NULL || dest == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

char	*ft_strdup(const char *src)
{
	int		l;
	char	*str;

	if (src == NULL)
		return (NULL);
	l = ft_strlen((char *)src);
	str = (char *)ft_calloc(sizeof(*str), (l + 1));
	if (str == NULL)
		return (NULL);
	str = ft_strcpy(str, src);
	return (str);
}

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




int ft_readlst(t_token *lst)
{
	if (!lst)
		return (1);
	if (lst->str && lst->next)
		lst = lst->next;
	printf("lst->str:");
	while (lst)
	{
		printf("|%s|", lst->str);
		lst = lst->next;
	}
	printf("\n\n");
	return (0);
}	



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