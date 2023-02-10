/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:10:32 by flplace           #+#    #+#             */
/*   Updated: 2023/02/10 14:04:18 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>

//						token type
//		type:	type de token, a distinguer pour le process global de tokenisation
//		str:	contenu sous forme de string du token (commande, string a traiter, etc )

// typedef struct s_token
// {
//     enum TOKEN_TYPE	type;
//     char			*str;
// 	struct s_token	*next;
// } t_token;

//						env type
//		id:		identifiant de la variable
//		vars:	variables sous formes de liste chainee.

typedef struct s_env
{
	char			*key;
    char			*value;
	struct s_env	*next;
} t_env;


/*			env building			*/
int			ft_env_reader(char **envp, t_env **envt);
t_env		*ft_lstadd_env(char *str, t_env **envt);
char		*ft_split_value(char *str);
char		*ft_split_key(char *str);
t_env		*ft_envlast(t_env *lst);



/*			lib utils				*/
void 		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
int 		ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *src);
char 		*ft_strndup(const char *src, size_t n);
size_t		ft_strlen(const char *str);
size_t		ft_strclen(char *str, char c);
char		*ft_strcpy(char *dest, const char *src);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strchr(char *str, int c);


void		ft_add_history(char *line);


int		 	ft_count_quote(char *str);

// int 	ft_readlst(t_token *lst);

char		*ft_expand(char *line);

/*						*/

void		env_printer(t_env **envt);
