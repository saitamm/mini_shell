/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:07:42 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 13:08:13 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_execution_built(t_minishell *strct)
{
	int	size;

	size = ft_lstsize_minishell(strct);
	if (size == 1 && is_built(strct->cmd[0]))
	{
		if (redirection_buils(strct))
			return (0);
		ft_builtins(strct);
		ft_underscore(strct);
		dup2(g_global->save_fd_out, STDOUT_FILENO);
		dup2(g_global->save_fd_int, STDIN_FILENO);
		return (0);
	}
	return (1);
}

void	help_wait(int status)
{
	if (WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		g_global->exit_status = 130;
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
		g_global->exit_status = 131;
	}
}

void	ft_wait(int size)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < size)
	{
		waitpid(g_global->pid[i], &status, 0);
		if (i == size - 1)
		{
			if (WIFEXITED(status))
				g_global->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				help_wait(status);
		}
		i++;
	}
}

void	ft_child(t_minishell *strct, int i)
{
	g_global->pid[i] = fork();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (g_global->pid[i] == 0)
		ft_exec_child(strct);
}
