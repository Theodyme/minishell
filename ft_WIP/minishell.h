/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:10:32 by flplace           #+#    #+#             */
/*   Updated: 2023/04/05 15:38:36 by mabimich         ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


# define C_ALPHA "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
# define C_ALPHANUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_\
0123456789"
# define C_BLANK "\t\r\v\f\n "

extern int	g_status;

enum	e_TOKEN_TYPE
{
	WORD, // 0
	QUOTE, // 1
	DQUOTE, // 2
	PIPE, // 3
	REDIR_IN, // pensez a check pipe a la fin de commande
	REDIR_OUT,
	APPEND,
	HEREDOC,
	DELIMITER,
	BLANK,
	EOL
};

/* -------------------------------- env type -------------------------------- */
/*
** 		key:		identifiant de la variable
** 		vars:	variables sous formes de liste chainee.
*/

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}					t_env;

/* ------------------------------- token type ------------------------------- 	*/
/*
** 		type:	type de token, a distinguer pour le process global de tokenisation
** 		str:	contenu sous forme de string du token (commande, string a traiter, etc)
*/

typedef struct s_token
{
	enum e_TOKEN_TYPE	type;
	char				*str;
	struct s_token		*next;
}						t_token;

typedef struct s_redir
{
	enum e_TOKEN_TYPE	type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_arg
{
	char			*str; // a verifier si encore utile
	struct s_arg	*next;
}					t_arg;

/* -------------------------- command division type ------------------------- */

typedef struct s_cmd
{
	char			*name;
	char			**argv;
	struct s_arg	*args_list;
	struct s_redir	*redir;
	t_env			*envt;
	char			**envp;
	pid_t			pid;
	int				fd[2];
	char			*name_file[2];
	int				status;
	struct s_cmd	*head;
	struct s_cmd	*next;
}	t_cmd;

/* -------------- function prototype for the array of pointers -------------- */

typedef int (*t_bltin)(t_cmd *cmd);

/* -------------------- array of function pointers struct ------------------- */

typedef struct t_fn
{
	char *call;
	t_bltin blt_fn;
} t_fn;

/* ----------------------------- title printing ----------------------------- */

void	ft_print_title(void);

/* ------------------------------ env building ------------------------------ */

int		ft_env_reader(char **envp, t_env **envt);
t_env	*ft_lstadd_env(char *str, t_env **envt);
char	*ft_split_value(char *str);
char	*ft_split_key(char *str);
t_env	*ft_envlast(t_env *lst);
void	ft_clear_env(t_env *envt);
void	ft_setting_env(t_env *envt, t_cmd *cmd);

/* -------------------------------- lib utils ------------------------------- */

void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	ft_strcat(char *dst, char *src);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
size_t	ft_strclen(const char *str, char c);
char	*ft_strcpy(char *dest, const char *src);
int		ft_is_in_charset(const char c, const char *charset);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_tab(char **tab);
char	*ft_strjoin_free(char *s1, char *s2);
void	ft_free_tab_str(char **tab, int max);
char	*ft_itoa(int n);
char	*ft_strtrim_free(char *s1, char const *set);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_2strjoin_with_free(char *s1, char *s2, size_t val);
char	*ft_3strjoin_with_free(char *s1, char *s2, char *s3, size_t val);
void	ft_msg(char *s1, char *s2);
void	ft_putstr_fd(char const *str, int fd);
void	ft_putendl_fd(char const *s, int fd);
char	*ft_pick(char const *s, char c, size_t p);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_tab_with_1blank(char **tab);

/* -------------------------------- builtins -------------------------------- */

int		ft_bltin_tester(t_cmd **cmd);

int		ft_bltin_echo(t_cmd *cmd);
int		ft_bltin_cd(t_cmd *cmd);
int		ft_bltin_pwd(t_cmd *cmd);
int		ft_bltin_export(t_cmd *cmd);
int		ft_bltin_unset(t_cmd *cmd);
int		ft_bltin_env(t_cmd *cmd);
int		ft_bltin_exit(t_cmd *cmd);
int		ft_bltin_echo(t_cmd *cmd);
int		ft_bltin_cd(t_cmd *cmd);
int		ft_bltin_pwd(t_cmd *cmd);
int		ft_bltin_export(t_cmd *cmd);
int		ft_bltin_unset(t_cmd *cmd);
int		ft_bltin_env(t_cmd *cmd);
int		ft_bltin_exit(t_cmd *cmd);

/* ----------------------------- builtins utils ----------------------------- */

int		ft_array_cntr(char **array);
t_env	*ft_key_add(t_env **envt, char *key, char *value);
t_env	*ft_key_finder(t_env **envt, char *needle);
int		ft_key_freer(char *key, char *value);
int		ft_key_remove(t_env *rm);
char	*ft_pathbuilder(char *path, char *cmdname);
int		ft_pwd_changer(t_cmd *cmd, char *path);

/* --------------------------------- EXPAND --------------------------------- */

int		ft_trim_blank(char *line);

int		ft_expand(t_token *tkn, t_env *env);

int		ft_wordlen(char *line);
int		ft_wordlen_with_dollar(char *line);

int		ft_getenv(char *key, t_env *env);
t_token	*ft_tokenize(char *line);

/* --------------------------------- PARSER --------------------------------- */

t_cmd  *ft_parser(t_token *tkn, t_env *envt);
int ft_check_syntax(t_token *tkn);
int ft_is_redir(t_token *tkn);
int		ft_check_syntax(t_token *tkn);
int		ft_is_redir(t_token *tkn);

/* --------------------------------- FILL_CMD ------------------------------- */

int		ft_fill_cmd(t_cmd *cmd, t_token *tkn);
int		ft_create_arg(t_arg **arg);
int		ft_add_arg(t_arg *arg, char *str);
int		ft_redir(t_token *token, t_cmd *cmd);
int		ft_add_redir(t_redir *redir, t_token *token);

/* --------------------------------- GET_PATH ------------------------------ */
char	*verif_paths(char **paths, char *cmd);
char	*get_path(char *cmd, char **envp);

/* ---------------------------------  --------------------------------- */

char	*ft_strtok_minishell(char *str, char *delim);

/* --------------------------------- EXEC --------------------------------- */

int		ft_exec(t_cmd *cmd);

/* --------------------------------- EXIT --------------------------------- */

void	dispatch_exit(t_cmd *cmd, int code);
void	dispatch_exit2(t_cmd *cmd, int code);
void	close_pipes(t_cmd *cmd);

/* ------------------------------ TO REORGANIZE ----------------------------- */

void	ft_add_history(char *line);

int		ft_count_quote(char *str);
int		ft_quotelen(char *str);

void	ft_free_lst_token(t_token *head);
void	ft_free_lst_env(t_env *head);

// int 	ft_readlst(t_token *lst);

/* -------------------------------------------------------------------------- */

t_token	*ft_specialtoken2(int *i, char *line, t_token *token);

int		ft_getenv(char *key, t_env *env);
t_token	*ft_tokenize(char *line);

/*				print test functions				*/

void	ft_print_token(t_token *head);
void	ft_print_env(t_env *head);
void	ft_print_array(char **array);
void	ft_print_cmd(t_cmd *cmd);

#endif
