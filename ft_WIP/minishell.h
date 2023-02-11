/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:10:32 by flplace           #+#    #+#             */
/*   Updated: 2023/02/11 14:33:09 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>

enum TOKEN_TYPE
{
	WORD, // commande ou argument
	QUOTE,
	DQUOTE,
	PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	APPEND, // >>
	HEREDOC, // <<
	DELIMITER,
	ENV
};

typedef struct s_list
{
	char	        *content;
	struct t_list	*next;
}   t_list;

//						token type
//		type:	type de token, a distinguer pour le process global de tokenisation
//		str:	contenu sous forme de string du token (commande, string a traiter, etc )

typedef struct s_token
{
	enum TOKEN_TYPE	type;
	char			*str;
	struct s_token	*next;
}   t_token;

//						env type
//		id:		identifiant de la variable
//		vars:	variables sous formes de liste chainee.

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}   t_env;

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
char		*ft_strndup(const char *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);
size_t		ft_strclen(const char *str, char c);
char		*ft_strcpy(char *dest, const char *src);

/*			builtins				*/
void		ft_bltin_env(t_env **envt);
void		ft_bltin_pwd(t_env **envt);
t_env		*ft_bltin_unset(t_env **envt, char *key);
int			ft_bltin_export(t_env **envt, char *key, char *value);

/*			builtins utils			*/
t_env		*ft_key_finder(t_env **envt, char *needle);
int			ft_key_remove(t_env *rm);
t_env		*ft_key_add(t_env **envt, char *key, char *value);


void		ft_add_history(char *line);


int 		ft_count_quote(char *str);
int			ft_quotelen(char *str);

// int 	ft_readlst(t_token *lst);


/*						*/

t_token	*ft_specialtoken2(int *i, char *line, t_token *token);

/*               EXPAND              */
int     ft_expand(t_token *tkn, t_env *env);
int     ft_trim_blank(char *line);

int     ft_wordlen(char *line);
int     ft_wordlen_with_dollar(char *line);

char	*ft_strchr(const char *s, int c);
void	env_printer(t_env **envt);

t_token	*ft_specialtoken2(int *i, char *line, t_token *token);

/*               EXPAND              */
int     ft_expand(t_token *tkn, t_env *env);
int     ft_trim_blank(char *line);

int     ft_wordlen(char *line);
int     ft_wordlen_with_dollar(char *line);

char	*ft_strchr(const char *s, int c);

int     ft_getenv(char *key, t_env *env);
t_token	*ft_tokenize(char *line);
