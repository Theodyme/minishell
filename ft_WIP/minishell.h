#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>

enum TOKEN_TYPE
{
    QUOTE,
    WORD, // commande ou argument
    PIPE, // |
    REDIR_IN, // <
    REDIR_OUT, // >
    APPEND, // >>
    HEREDOC, // <<
    DELIMITER
};

typedef struct s_list
{
	char	        *content;
    struct t_list	*next;
} t_list;

//						token type
//		type:	type de token, a distinguer pour le process global de tokenisation
//		str:	contenu sous forme de string du token (commande, string a traiter, etc )

typedef struct s_token
{
    enum TOKEN_TYPE	type;
    char			*str;
    struct s_token	*next;
} t_token;

//						env type
//		id:		identifiant de la variable
//		vars:	variables sous formes de liste chainee.

typedef struct s_env
{
    char            *name;
    struct  t_list   *vars;
    struct  s_env    *next;
} t_env;

/*			env building			*/

/*			lib utils				*/
void 	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
int 	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *src);
char    *ft_strndup(const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);

void	ft_add_history(char *line);


int 	ft_count_quote(char *str);
int     ft_quotelen(char *str);

// int 	ft_readlst(t_token *lst);

char    *ft_expand(char *line);

/*						*/
void	*ft_lstlast(void *lst);


t_token	*ft_specialtoken2(int *i, char *line, t_token *token);
