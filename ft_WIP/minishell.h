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

typedef struct s_token
{
    enum TOKEN_TYPE type;
    char *str;
    struct s_token *next;
} t_token;


/*			lib utils				*/
void 	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
int 	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);

void	ft_add_history(char *line);


int 	ft_count_quote(char *str);
int     ft_quote(char *str, t_token *head);

char    *ft_expand(char *line);
