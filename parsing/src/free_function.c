/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:49:41 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/28 15:32:16 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	ft_free_data(t_data **data)
{
	t_data	*k;

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

void	ft_free_file(t_file **lst)
{
	t_file	*k;

	if (!lst)
		return ;
	while (*lst)
	{
		k = *lst;
		free((*lst)->file);
		*lst = (*lst)->next;
		free(k);
	}
	*lst = NULL;
}

void	free_minishell(t_minishell **m_shell)
{
	t_minishell	*k;

	if (!m_shell)
		return ;
	while (*m_shell)
	{
		k = *m_shell;
		ft_free((*m_shell)->cmd, len_double_str((*m_shell)->cmd));
		ft_free_file(&(*m_shell)->files);
		*m_shell = (*m_shell)->next;
		free(k);
	}
	*m_shell = NULL;
}
