/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:46:24 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/05 19:13:24 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	help_1_ft_outfile(t_file *strct)
{
	write(2, "Minishell:", 11);
	write(2, strct->file, ft_strlen(strct->file));
	write(2, ": ambiguous redirect\n", 22);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	close(g_global->fd_pipe[1]);
	close(g_global->fd_pipe[0]);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	ft_free_global();
	free(g_global);
	exit(1);
}

int	help_2_ft_outfile(t_file *strct, int outfile_fd)
{
	write(2, "Minishell:", 11);
	perror(strct->file);
	free_minishell(&g_global->strct);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	close(g_global->fd_pipe[1]);
	close(g_global->fd_pipe[0]);
	free(g_global->pid);
	ft_free_global();
	free(g_global);
	close(outfile_fd);
	exit(1);
}

int	ft_outfile(t_file *strct)
{
	int	outfile_fd;

	if (strct->flag == AMB)
		help_1_ft_outfile(strct);
	outfile_fd = open(strct->file, O_CREAT | O_TRUNC | O_WRONLY, 0640);
	if (outfile_fd == -1)
		help_2_ft_outfile(strct, outfile_fd);
	if (ft_strcmp(strct->file, "/dev/stdout"))
	{
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		{
			write(2, "Error with dup2\n", 17);
			g_global->exit_status = 1;
			close(outfile_fd);
			return (1);
		}
		close(outfile_fd);
		return (0);
	}
	return (0);
}
