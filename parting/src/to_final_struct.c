/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_final_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:47:36 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/06 18:56:52 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_minishell *lstlast_minishell(t_minishell *lst)
{
    if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
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

char    **command_to_array(t_cmd *d)
{
    int     size;
    char    **cmd;
    int     i;

    size = ft_lstsize(d);
    cmd = malloc((size + 1) *sizeof(char *));
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
void    to_final_struct(t_data *data, t_minishell **strct)
{
    t_data  *d;
    t_minishell *s;
    t_minishell *k;

    d = data;
    while (d)
    {
        s = malloc(sizeof(t_minishell));
        if (!s)
            return ;
        s->files = NULL;
        s->cmd = command_to_array(d->command);
        s->files = d->files;
        s->next = NULL;
        k = *strct;
        if (!strct)
		    return ;
	    if (!*strct)
	    {
		    *strct = s;
        d = d->next;
		    continue;
	    }
        k = lstlast_minishell(*strct);
	    k->next = s;
        d = d->next;
    }
}


void	ft_free_cmd(t_cmd **lst)
{
	t_cmd	*k;

	if (!lst)
		return ;
	while (*lst)
	{
		k = *lst;
		free((*lst)->cmd);
		*lst = (*lst)->next;
		free(k);
	}
	*lst = NULL;
}

void    ft_free_data(t_data **data)
{
    t_data *k;
    if (!data)
        return ;
    while (*data)
    {
        k = *data;
        ft_free_cmd(&(*data)->command);
        *data = (*data)->next;
        free(k);
    }
    *data = NULL;
}

t_minishell *parce(char *line)
{
    char    **splt_line;
    t_minishell *str;
    t_data *data;

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
