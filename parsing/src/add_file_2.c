/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:40:04 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/26 14:32:47 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_file	*ft_lstlast_file(t_file *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
void	ft_lstadd_file(t_file **lst, char *str, t_file *new)
{
	t_file *k;
	char *src;

	new->flag = 0;
	src = ft_strdup(str);
	src = help_file(str, &new, src);
	new->file = src;
	new->next = NULL;
	k = *lst;
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	k = ft_lstlast_file(*lst);
	k->next = new;
}