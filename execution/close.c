/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:19:14 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 12:08:56 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_0(void)
{
	free_minishell(&g_global->strct);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	free(g_global->pid);
	ft_free_global();
	free(g_global);
	exit(0);
}

void	free_1(void)
{
	free_minishell(&g_global->strct);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	free(g_global->pid);
	ft_free_global();
	free(g_global);
}

void	free_2(t_minishell *strct, char **spl)
{
	write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
	write(2, ": command not found\n", 21);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	ft_free(spl, len_double_str(spl));
	ft_free_global();
	free(g_global);
	exit(127);
}

void	free_3(t_minishell *strct, char **spl)
{
	perror(strct->cmd[0]);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	ft_free(spl, len_double_str(spl));
	ft_free_global();
	free(g_global);
	exit(127);
}

void	free_4(t_minishell *strct, char **spl, int l)
{
	perror(strct->cmd[0]);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	ft_free(spl, len_double_str(spl));
	ft_free_global();
	close(l);
	free(g_global);
	exit(126);
}
