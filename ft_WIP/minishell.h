/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:10:32 by flplace           #+#    #+#             */
/*   Updated: 2023/03/01 18:51:21 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdbool.h>

#define ALPHA "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_" 
#define ALPHANUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

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
};

/* -------------------------------- env type -------------------------------- */
/*
** 		id:		identifiant de la variable
** 		vars:	variables sous formes de liste chainee.
*/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}   t_env;

/* ------------------------------- token type ------------------------------- 	*/
/*
** 		type:	type de token, a distinguer pour le process global de tokenisation
** 		str:	contenu sous forme de string du token (commande, string a traiter, etc)
*/

typedef struct s_token
{
	enum TOKEN_TYPE	type;
	char			*str;
	struct s_token	*next;
}   t_token;

/* -------------------------- command division type ------------------------- */
/*
**  POUR LES REDIRECTIONS !! : ajouter une liste chainee de redirections dans la struct div
*/

typedef struct s_cmd_div
{
    char     *cmd;
    char     **args;
    t_env	*envt;
    int      input;
    int      output;
    struct s_cmd_div    *next;
}   t_cmd_div;

/* ------------------------------ env building ------------------------------ */

int			ft_env_reader(char **envp, t_env **envt);
t_env		*ft_lstadd_env(char *str, t_env **envt);
char		*ft_split_value(char *str);
char		*ft_split_key(char *str);
t_env		*ft_envlast(t_env *lst);
void		ft_clear_env(t_env *envt);

/* -------------------------------- lib utils ------------------------------- */

void 		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
int 		ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *src);
char		*ft_strndup(const char *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);
size_t		ft_strclen(const char *str, char c);
char		*ft_strcpy(char *dest, const char *src);
int			ft_is_charset(char c, char *charset);
char		*ft_strjoin_tab(char **tab);
void		ft_free_tab_str(char **tab, int max);

/* -------------------------------- builtins -------------------------------- */

void		ft_bltin_env(t_cmd_div *div);
void		ft_bltin_pwd(t_cmd_div *div);
t_env		*ft_bltin_unset(t_cmd_div *div);
int			ft_bltin_export(t_cmd_div *div);
void		ft_bltin_echo(char *echo, int flag, int fdout);
void		ft_bltin_cd(t_cmd_div *div);

/* ----------------------------- builtins utils ----------------------------- */

t_env		*ft_key_finder(t_env **envt, char *needle);
int			ft_key_remove(t_env *rm);
t_env		*ft_key_add(t_env **envt, char *key, char *value);

/* --------------------------------- EXPAND --------------------------------- */

int			ft_expand(t_token *tkn, t_env *env);
int			ft_trim_blank(char *line);

int			ft_wordlen(char *line);
int			ft_wordlen_with_dollar(char *line);

int			ft_getenv(char *key, t_env *env);
t_token		*ft_tokenize(char *line);


void		ft_bltin_tester(char **line, t_env **envt);

size_t	ft_strlen(const char *str);
size_t	ft_strclen(const char *str, char c);

char	*ft_itoa(int n);

char	*ft_strtok_minishell(char *str, char *delim);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_tab(char **tab);
void	*ft_memmove(void *dst, const void *src, size_t n);

/* ------------------------------ TO REORGANIZE ----------------------------- */

void	ft_add_history(char *line);


int 	ft_count_quote(char *str);
int     ft_quotelen(char *str);

void	ft_free_lst_token(t_token *head);
void	ft_free_lst_env(t_env *head);


// int 	ft_readlst(t_token *lst);

/* -------------------------------------------------------------------------- */

t_token	*ft_specialtoken2(int *i, char *line, t_token *token);

char	*ft_strchr(const char *s, int c);

int     ft_getenv(char *key, t_env *env);
t_token	*ft_tokenize(char *line);


/*				test functions				*/

void	ft_print_token(t_token *head);

#endif