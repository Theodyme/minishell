#include "../minishell.h"

static size_t	ft_nblen_itoa(int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		i++;
	while (nb >= 10 || nb <= -10)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		nc;
	long	nb;

	nb = n;
	nc = ft_nblen_itoa(nb);
	r = (char *)ft_calloc((nc + 1), sizeof(*r));
	if (r == NULL)
		return (NULL);
	r[nc] = '\0';
	if (!nb)
		r[0] = '0';
	if (nb < 0)
	{
		r[0] = '-';
		nb *= -1;
	}
	while (nb)
	{
		r[--nc] = ((nb % 10) + '0');
		nb /= 10;
	}
	return (r);
}