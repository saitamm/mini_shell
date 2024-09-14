/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:36:48 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/14 15:56:00 by sait-amm         ###   ########.fr       */
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
	src = help_file(str, &new , src);
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
	int		i;
	char	*s;
	
	a = 0;
	i = 0;
	s = ft_strdup(str);
	// printf("***************%s\n", s);
	while (need_expand(s, &i))
	{
		// printf(":::::::::::::::\n");
		s = expand_str(s, i);
	}
	// printf("***************%s\n", s);
	cmd_plt = split_str(s, &a);
	return (cmd_plt);
}

void    ft_lstadd_cmd(t_cmd **head, char *file_cmd)
{
    t_cmd   *s;
    t_cmd   *k;
	char	**cmd_split;
	size_t i = 0 ;
	
   	cmd_split = help_cmd(file_cmd);
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
	ft_free(cmd_split, len_double_str(cmd_split));
}

t_data	*ft_lstlast_data(t_data *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
