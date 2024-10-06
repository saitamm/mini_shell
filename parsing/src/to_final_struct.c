/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_final_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:47:36 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/06 11:30:33 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_lstsize(t_cmd *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**command_to_array(t_cmd *d)
{
	int		size;
	char	**cmd;
	int		i;

	size = ft_lstsize(d);
	cmd = malloc((size + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (d)
	{
		cmd[i] = ft_strdup(d->cmd);
		d = d->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_minishell	*new_node_minishell(t_cmd *cmd, t_file *files)
{
	t_minishell	*s;

	s = malloc(sizeof(t_minishell));
	if (!s)
		return (NULL);
	s->files = NULL;
	s->cmd = command_to_array(cmd);
	s->files = files;
	s->next = NULL;
	return (s);
}

void	to_final_struct(t_data *data, t_minishell **strct)
{
	t_data		*d;
	t_minishell	*s;
	t_minishell	*k;

	d = data;
	while (d)
	{
		s = new_node_minishell(d->command, d->files);
		k = *strct;
		if (!strct)
			return ;
		if (!*strct)
		{
			*strct = s;
			d = d->next;
			continue ;
		}
		k = lstlast_minishell(*strct);
		k->next = s;
		d = d->next;
	}
}

t_minishell	*parce(char *line)
{
	char		**splt_line;
	t_minishell	*str;
	t_data		*data;

	data = NULL;
	str = NULL;
	if (parce_error(line))
		return (NULL);
	splt_line = ft_split_with_pipe(line);
	init_data(&data, splt_line);
	to_final_struct(data, &str);
	ft_free(splt_line, len_double_str(splt_line));
	ft_free_data(&data);
	return (str);
}
