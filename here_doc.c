/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:20:52 by mabimich          #+#    #+#             */
/*   Updated: 2023/10/11 17:58:54 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Here_doc
**	@data : structure contenant les données du programme
**
**	Cette fonction lit sur l'entrée standard jusqu'à ce que la chaine de
**	caractère passée en argument soit lue. La chaine de caractère est ensuite
**	écrite dans un fichier temporaire.
** 	Le fichier temporaire est ensuite ouvert par le processus parent.
*/

void	init_heredoc(t_redir *redir)
{
	redir->delimiter = ft_strdup(redir->file);
	free(redir->file);
	redir->file = ft_create_fname(NAME_TMP_FILE);
}

int	here_doc(t_redir *redir)
{
	char	*ret;
	int		len;
	char	*joined_ret;

	len = 1;
	redir->fd_h_d = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	signal(SIGINT, sig_heredoc);
	while (redir->fd_h_d != -1 && len != -1)
	{
		ret = readline("heredoc > ");
		if (ret == NULL
			|| !ft_strncmp(ret, redir->delimiter, ft_strlen(redir->delimiter)))
		{
			break ; // AJOUTER UNE CONDITION POUR CTRL D COMME EOF readline = NULL
		}
		joined_ret = ft_strjoin(ret, "\n");
		len = write(redir->fd_h_d, joined_ret, ft_strlen(ret) + 1);
		free(joined_ret);
		free(ret);
		ret = NULL;
	}
	if (ret)
		free(ret);
	close(redir->fd_h_d);
	open(redir->file, O_RDONLY);
	return (redir->fd_h_d);
}
