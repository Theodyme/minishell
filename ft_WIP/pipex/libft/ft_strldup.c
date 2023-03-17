#include "libft.h"

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