/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:36:48 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/29 21:35:05 by lai-elho         ###   ########.fr       */
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


void	ft_lstadd_file(t_file **lst, char *str)
{
	t_file	*k;
    t_file  *s;
	char	*src;

    s = (t_file *)malloc(sizeof(t_file));
	s->flag = 0;
	src = ft_strdup(str);
	src = help_file(str, &s , src);
    s->file = src;
    s->next = NULL;
    k = *lst;   
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = s;
		return ;
	}
	k = ft_lstlast_file(*lst);
	k->next = s;
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
char	**help_cmd(char *str)
{
	char	**cmd_plt;
	int		a;
	
	a = 0;
	while (need_expand(str))
		str = expand_str(str);
	cmd_plt = split_str(str, &a);
	return (cmd_plt);
}

void    ft_lstadd_cmd(t_cmd **head, char *str)
{
    t_cmd   *s;
    t_cmd   *k;
	char	**cmd_split;
	size_t i = 0 ;

   	cmd_split = help_cmd(str);
	if (!cmd_split)
		return ;
	i= 0 ;
	while (i < len_double_str(cmd_split))
	{
		s = malloc(sizeof(t_cmd));
		if (!s)
			return ;
		s->cmd = ft_strdup(cmd_split[i]);
    	s->next = NULL;
    	k = *head;
		if (!head)
			return ;
		if (!*head)
			{
			*head = s;
			i++;
			continue;
			}			
		k = ft_lstlast_cmd(*head);
		k->next = s;
		i++;
	}
}

t_data	*ft_lstlast_data(t_data *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
