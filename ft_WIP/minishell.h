/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:10:32 by flplace           #+#    #+#             */
/*   Updated: 2023/03/15 15:36:29 by flplace          ###   ########.fr       */
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

/* -------------------------------------------------------------------------- */

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
	BLANK
};

/* -------------------------------- env type -------------------------------- */
/*
** 		key:		identifiant de la variable
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

typedef struct s_cmd
{
    char			*name;
    char			**args;
    struct s_redir	*redir;
    t_env			*envt;
    struct s_cmd	*next;
    struct s_arg	*args_list;
}   t_cmd;

/* -------------- function prototype for the array of pointers -------------- */

typedef int	(*t_bltin)(t_cmd *cmd);

/* -------------------- array of function pointers struct ------------------- */

typedef struct t_fn
{
	char	*call;
	t_bltin	blt_fn;
}		t_fn;

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
void		*ft_memmove(void *dst, const void *src, size_t n);
int 		ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *src);
char		*ft_strndup(const char *src, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
size_t		ft_strclen(const char *str, char c);
char		*ft_strcpy(char *dest, const char *src);
int			ft_is_charset(char c, char *charset);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_tab(char **tab);
char		*ft_strjoin_free(char *s1, char *s2);
void		ft_free_tab_str(char **tab, int max);
char		*ft_itoa(int n);

/* -------------------------------- builtins -------------------------------- */

int			ft_bltin_tester(t_cmd *cmd)
;

int			ft_bltin_echo(t_cmd *cmd);
int			ft_bltin_cd(t_cmd *cmd);
int			ft_bltin_pwd(t_cmd *cmd);
int			ft_bltin_export(t_cmd *cmd);
int			ft_bltin_unset(t_cmd *cmd);
int			ft_bltin_env(t_cmd *cmd);
int			ft_bltin_exit(t_cmd *cmd);

/* ----------------------------- builtins utils ----------------------------- */

int			ft_array_cntr(char **array);
t_env		*ft_key_add(t_env **envt, char *key, char *value);
t_env		*ft_key_finder(t_env **envt, char *needle);
int			ft_key_freer(char *key, char *value);
int			ft_key_remove(t_env *rm);

/* --------------------------------- EXPAND --------------------------------- */

int			ft_expand(t_token *tkn, t_env *env);
int			ft_trim_blank(char *line);

int			ft_wordlen(char *line);
int			ft_wordlen_with_dollar(char *line);

int			ft_getenv(char *key, t_env *env);
t_token		*ft_tokenize(char *line);


char		*ft_strtok_minishell(char *str, char *delim);

size_t	ft_strlen(const char *str);
size_t	ft_strclen(const char *str, char c);

char	*ft_itoa(int n);

char	*ft_strtok_minishell(char *str, char *delim);


void	*ft_memmove(void *dst, const void *src, size_t n);
char		*ft_strjoin_tab(char **tab);

/* ------------------------------ TO REORGANIZE ----------------------------- */

void		ft_add_history(char *line);


int 		ft_count_quote(char *str);
int			ft_quotelen(char *str);

void		ft_free_lst_token(t_token *head);
void		ft_free_lst_env(t_env *head);


// int 	ft_readlst(t_token *lst);

/* -------------------------------------------------------------------------- */

t_token		*ft_specialtoken2(int *i, char *line, t_token *token);


int			ft_getenv(char *key, t_env *env);
t_token		*ft_tokenize(char *line);


/*				test functions				*/

void		ft_print_token(t_token *head);

#endif
