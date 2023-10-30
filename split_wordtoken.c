/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:43:03 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/30 21:43:26 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_create_two_tkn_for_split_wtkn(t_token *tkn, char *str, int *i)
{
	t_token	*save_next;

	save_next = tkn->next;
	tkn->next = ft_calloc(1, sizeof(t_token));
	if (!tkn->next)
		return (1);
	tkn = tkn->next;
	tkn->str = ft_strdup(" ");
	if (!tkn->str)
		return (1);
	tkn->type = BLANK;
	tkn->next = ft_calloc(1, sizeof(t_token));
	if (!tkn->next)
		return (1);
	tkn = tkn->next;
	tkn->str = ft_strndup(&str[*i], ft_strsetlen(&str[*i], C_BLANK));
	tkn->next = save_next;
	tkn->type = QUOTE;
	*i += ft_strsetlen(&str[*i], C_BLANK) + 1;
	return (0);
}

int	ft_split_wordtoken(t_token *tkn)
{
	t_token	*save_next;
	char	*save;
	int		i;

	if (!tkn)
		return (1);
	if (tkn->type != WORD || !ft_strchrset(tkn->str, C_BLANK))
		return (0);
	save = tkn->str;
	save_next = tkn->next;
	i = ft_strsetlen(save, C_BLANK) + 1;
	tkn->str = ft_strndup(save, ft_strsetlen(save, C_BLANK));
	if (!tkn->str)
		return (1);
	while (save && save[i - 1])
	{	
		if (ft_create_two_tkn_for_split_wtkn(tkn, save, &i))
			return (1);
		if (tkn->next->next)
			tkn = tkn->next->next;
		else
			return (1);
	}
	free(save);
	return (tkn->next = save_next, 0);
}
