/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 13:08:15 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_close_parent(t_minishell *strct)
{
	close(g_global->fd_pipe[1]);
	dup2(g_global->fd_pipe[0], STDIN_FILENO);
	close(g_global->fd_pipe[0]);
	g_global->exit_status = 0;
	ft_underscore(strct);
}

void	ft_execute_mult_pip(t_minishell *strct)
{
	int	size;
	int	i;

	i = 0;
	size = ft_lstsize_minishell(strct);
	g_global->pid = malloc(size * sizeof(int));
	if (!g_global->pid)
		return ;
	while (strct)
	{
		if (pipe(g_global->fd_pipe) == -1)
		{
			perror("pipe error");
			ft_free_global();
			return ;
		}
		else
			ft_child(strct, i);
		ft_close_parent(strct);
		strct = strct->next;
		i++;
	}
	ft_wait(size);
	free(g_global->pid);
}

void	ft_execution(t_minishell *strct)
{
	if (!ft_execution_built(strct))
		return ;
	else
		ft_execute_mult_pip(strct);
}
