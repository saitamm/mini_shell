/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function_built.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:06:43 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/05 03:51:06 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_1_in_exit(void)
{
	if (ft_lstsize_minishell(g_global->strct))
	{
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		close(g_global->fd_pipe[1]);
		close(g_global->fd_pipe[0]);
	}
	free_minishell(&g_global->strct);
	free_list(&g_global->env);
	if (g_global->pwd)
		free(g_global->pwd);
	if (g_global->oldpwd)
		free(g_global->oldpwd);
	if (g_global->underscore)
		free(g_global->underscore);
	free(g_global);
}

void	ft_free_2_in_exit(void)
{
	free_minishell(&g_global->strct);
	free_list(&g_global->env);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	if (g_global->pwd)
		free(g_global->pwd);
	if (g_global->oldpwd)
		free(g_global->oldpwd);
	if (g_global->underscore)
		free(g_global->underscore);
	if (g_global->pid)
		free(g_global->pid);
	free(g_global);
}

void	ft_free_3_in_exit(char **cmd)
{
	write(2, "exit \nMinishell: exit: ", 24);
	write(2, cmd[1], ft_strlen(cmd[1]));
	write(2, ": numeric argument required\n", 29);
	if (ft_lstsize_minishell(g_global->strct))
	{
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		close(g_global->fd_pipe[1]);
		close(g_global->fd_pipe[0]);
	}
	free_minishell(&g_global->strct);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	free_list(&g_global->env);
	if (g_global->pwd)
		free(g_global->pwd);
	if (g_global->oldpwd)
		free(g_global->oldpwd);
	if (g_global->underscore)
		free(g_global->underscore);
	if (g_global->pid)
		free(g_global->pid);
	free(g_global);
}
