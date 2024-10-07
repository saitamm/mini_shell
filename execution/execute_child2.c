/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:59:33 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/07 12:14:22 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_builtins_3(t_minishell *strct)
{
	int	ex;

	if (ft_strcmp(strct->cmd[0], "echo") == 0)
	{
		ex = ft_echo(strct->cmd);
		free_1();
		exit(ex);
	}
	else if (ft_strcmp(strct->cmd[0], "cd") == 0)
	{
		ex = ft_cd(strct->cmd);
		free_1();
		exit(ex);
	}
}

void	handle_builtins_2(t_minishell *strct)
{
	int	ex;

	if (ft_strcmp(strct->cmd[0], "unset") == 0)
	{
		ex = unset(strct->cmd);
		free_1();
		exit(ex);
	}
	else if (ft_strcmp(strct->cmd[0], "export") == 0)
	{
		ft_export(strct);
		ex = g_global->exit_status;
		free_1();
	}
	else if (ft_strcmp(strct->cmd[0], "exit") == 0)
	{
		ex = ft_exit(strct->cmd);
		free_1();
		exit(ex);
	}
	handle_builtins_2(strct);
}

void	handle_builtins(t_minishell *strct)
{
	int	ex;

	if (ft_strcmp(strct->cmd[0], "pwd") == 0)
	{
		ex = ft_pwd();
		free_1();
		exit(ex);
	}
	else if (ft_strcmp(strct->cmd[0], "env") == 0)
	{
		ex = print_env(g_global->env, strct->cmd);
		free_1();
		exit(ex);
	}
	handle_builtins_2(strct);
	handle_builtins_3(strct);
}

void	handle_special(t_minishell *strct)
{
	if (!ft_strcmp(strct->cmd[0], "."))
	{
		write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
		write(2, ": .: filename argument required\n", 33);
		write(2, ".: usage: . filename [arguments]", 33);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(126);
	}
	else if (!ft_strcmp(strct->cmd[0], ".."))
	{
		write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
		write(2, "command not found\n", 19);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(126);
	}
}
