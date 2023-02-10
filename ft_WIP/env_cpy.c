/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flplace <flplace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:58:45 by flplace           #+#    #+#             */
/*   Updated: 2023/02/10 11:22:27 by flplace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*		char	*ft_split_key(char *str)				*/
/*														*/
/*			recupere toute la partie avant le signe =	*/
/*			et la renvoie.								*/
/*														*/
/*			renvoie la valeur de key sous forme de		*/
/*			string.										*/

char	*ft_split_key(char *str)
{
	char	*key;

	key = ft_calloc(sizeof(char), ft_strclen(str, '=') + 1);
	if (key == NULL)
		return (NULL);
	key = ft_strndup(str, ft_strclen(str, '='));
	return (key);
}

/*		char	*ft_split_value(char *str)				*/
/*														*/
/*			recupere toute la partie apres le signe =	*/
/*			et la renvoie.								*/
/*														*/
/*			renvoie la valeur de value sous forme de	*/
/*			string.										*/

char	*ft_split_value(char *str)
{
	char	*value;

	str += ft_strclen(str, '=') + 1;
	value = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (value == NULL)
		return (NULL);
	value = ft_strdup(str);
	return (value);
}

/*		t_env	*ft_lstadd_env(char *str)				*/
/*														*/
/*			cree un nouveau maillon de type env.		*/
/*			et le complete avec les valeurs de key et	*/
/*			value.										*/

t_env	*ft_lstadd_env(char *str, t_env **envt)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = ft_split_key(str);
	new->value = ft_split_value(str);
	new->next = NULL;
	if (!(*envt))
	{
		*envt = new;
		return (new);
	}
	last = ft_envlast(*envt);
	last->next = new;
	return (new);
}

/*		t_env	*env_reader(char **env)					*/
/*														*/
/*			parcourt avec i la variable env.			*/
/*			pour chaque iteration, appelle la			*/
/*			creation d'un nouveau maillon contenant		*/
/*			NAME et la liste VALUES.					*/
/*														*/
/*			renvoie un pointeur vers le premier			*/
/*			maillon de la liste chainee nouvellement	*/
/*			creee.										*/

void	ft_env_reader(char **envp, t_env **envt)
{
	int		i;

	i = -1;
	while(envp[++i])
	{
		// printf("envp = %s\n", envp[i]);
		ft_lstadd_env(envp[i], envt);
	}
	return ;
}
