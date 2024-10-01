/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:40:04 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/01 11:58:23 by sait-amm         ###   ########.fr       */
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
	t_file	*k;
	char	*src;

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

void	ft_lstadd_cmd(t_cmd **head, char *file_cmd)
{
	t_cmd	*s;
	t_cmd	*k;
	char	**cmd_split;
	size_t	i;

	cmd_split = help_cmd(file_cmd);
	if (!cmd_split)
		return ;
	i = 0;
	while (i < len_double_str(cmd_split))
	{
		s = new_node_cmd(cmd_split[i++]);
		k = *head;
		if (!head)
			return ;
		if (!*head)
			*head = s;
		else
		{
			k = ft_lstlast_cmd(*head);
			k->next = s;
		}
	}
	ft_free(cmd_split, len_double_str(cmd_split));
}
