/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intfile2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:09:59 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/11 20:38:39 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	hepl_1_ft_infile(t_file *strct)
{
	write(2, "Minishell:", 10);
	write(2, strct->file, ft_strlen(strct->file));
	write(2, ": ambiguous redirect\n", 21);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	close(g_global->fd_pipe[1]);
	close(g_global->fd_pipe[0]);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	ft_free_global();
	free(g_global);
}

void	hepl_2_ft_infile(t_file *strct)
{
	write(2, "Minishell:", 10);
	perror(strct->file);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	close(g_global->fd_pipe[1]);
	close(g_global->fd_pipe[0]);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	ft_free_global();
	free(g_global);
}

void	hepl_3_ft_infile(t_file *strct, int infile_fd)
{
	write(2, "Minishell:", 10);
	perror(strct->file);
	g_global->exit_status = 1;
	close(infile_fd);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	close(g_global->fd_pipe[1]);
	close(g_global->fd_pipe[0]);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	ft_free_global();
	free(g_global);
}

void	hepl_4_ft_infile(void)
{
	perror("Error opening file\n");
	free_minishell(&g_global->strct);
	free(g_global->pid);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	close(g_global->fd_pipe[1]);
	close(g_global->fd_pipe[0]);
	ft_free_global();
	free(g_global);
}

void	hepl_5_ft_infile(int infile_fd)
{
	perror("Error in dup2\n");
	g_global->exit_status = 1;
	close(infile_fd);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	close(g_global->fd_pipe[1]);
	close(g_global->fd_pipe[0]);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	ft_free_global();
	free(g_global);
}
