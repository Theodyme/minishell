#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>

enum TOKEN_TYPE
{
    WORD,
    PIPE,
    REDIR
};

typedef struct s_list
{
	void	*content;
    struct t_list	*next;
} t_list;

//						token type
//		type:	type de token, a distinguer pour le process global de tokenisation
//		str:	contenu sous forme de string du token (commande, string a traiter, etc )

typedef struct s_token
{
    enum TOKEN_TYPE	type;
    char			*str;
} t_token;

//						env type
//		id:		identifiant de la variable
//		vars:	variables sous formes de liste chainee.

typedef struct s_env
{
	char	*id;
    struct t_list	*vars;
} t_env;


/*			env building			*/

/*			lib utils				*/
void 	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
int 	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);

void	ft_add_history(char *line);

int 	ft_count_quote(char *str);

// int 	ft_readlst(t_token *lst);

char    *ft_expand(char *line);

/*						*/
void	*ft_lstlast(void *lst);

