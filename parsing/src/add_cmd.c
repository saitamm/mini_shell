/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:40:57 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/02 14:47:30 by sait-amm         ###   ########.fr       */
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
char *help_norm_expand_cmd(char *string)
{
	int pos;
	char *new_src;
	pos = 0;
	while (need_expand(string, &pos))
	{
		new_src = expand_str(string, pos);
		free(string);
		string = ft_strdup(new_src);
		free(new_src);
	}
	return (string);
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
	s = help_norm_expand_cmd(s);
	cmd_plt = split_str(s, &a);
	free(s);
	return (cmd_plt);
}

t_cmd	*new_node_cmd(char *str)
{
	t_cmd	*s;

	s = malloc(sizeof(t_cmd));
	if (!s)
		return (NULL);
	s->cmd = ft_strdup(str);
	s->next = NULL;
	return (s);
}
