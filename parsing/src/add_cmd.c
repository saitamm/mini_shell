/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:40:57 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/23 12:51:44 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_cmd(int *i, t_data **s, char *str)
{
	char	*file_cmd;
	size_t	k;

	file_cmd = ft_file(str + (*i));
	k = ft_strlen(file_cmd);
	ft_lstadd_cmd(&(*s)->command, file_cmd);
	*i = *i + ft_skip(str + (*i)) + k;
	free(file_cmd);
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
	while (need_expand(s, &i))
		s = expand_str(s, i);
	cmd_plt = split_str(s, &a);
	free(s);
	return (cmd_plt);
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
		s = malloc(sizeof(t_cmd));
		if (!s)
			return ;
		s->cmd = ft_strdup(cmd_split[i++]);
		s->next = NULL;
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
