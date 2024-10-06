/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:10:35 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/06 13:54:44 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	no_red_af(char *str)
{
	int	i;

	i = 0;
	while (ft_whitespace(str[i]))
		i++;
	if (str[i] != '>' && str[i] != '<')
		return (1);
	return (0);
}

int	ft_skip(char *str)
{
	int	i;

	i = 0;
	while (ft_whitespace(str[i]) && str[i])
		i++;
	return (i);
}

t_minishell	*lstlast_minishell(t_minishell *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	unlink_here_doc()
{
	t_file	*file;

	file = g_global->strct->files;
	while (file)
	{
		if (file->file_type == HER_DOC)
			unlink(file->file);
		file = file->next;
	}
}
int	her_doc_sig(char *line)
{
	if (g_global->sig_herdoc == -1)
	{
		unlink_here_doc();
		g_global->exit_status = 130;
		norm_main(line);
		return (0);
	}
	return (1);
}
