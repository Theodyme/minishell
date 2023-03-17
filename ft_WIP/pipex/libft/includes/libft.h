/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:44:23 by mabimich          #+#    #+#             */
/*   Updated: 2023/03/17 17:33:12 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>

# define BUFFER_SIZE 1024

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_calloc_full(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char const *str, int fd);
char	**ft_split(char const *s, char c);
char	*ft_pick(char const *s, char c, size_t p);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strldup(const char *src, size_t len);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_2strjoin_with_free(char *s1, char *s2, size_t val);
char	*ft_3strjoin_with_free(char *s1, char *s2, char *s3, size_t val);
size_t	ft_strlcat(char *dest, const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *m, const char *a, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_free_tab_str(char **tab, int max);

char	*get_next_line(int fd);
char	*get_line(char *tab, size_t fd);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
int		ft_strclen_gnl(const char *str, int len, char c);

size_t	ft_strclen(char *str, char c);
int		ft_printf(const char *par, ...);
size_t	ft_putstr(char const *s);
size_t	ft_putnbr(long long nb, size_t i);
size_t	ft_putchar(int c);
size_t	ft_putcstr(char *str, char c);
size_t	ft_nblen(long long nb);
size_t	ft_putn_b(unsigned long long nbr, char *base, size_t i);
size_t	ft_dispatch_nb(unsigned long long nbr, char c);

char	*ft_get_extension(char *name_file);
char	*ft_create_fname(char *fname);

#endif
