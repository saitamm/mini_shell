/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:17:14 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/05 18:53:50 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	help1_append(t_file *strct, int fd)
{
	write(2, "Minishell:", 11);
	perror(strct->file);
	g_global->exit_status = 1;
	close(fd);
	ft_free_global();
	exit(g_global->exit_status);
}

int	ft_append(t_file *strct)
{
	int	fd;

	if (strct->flag == AMB)
	{
		write(2, "Minishell:", 11);
		write(2, strct->file, ft_strlen(strct->file));
		write(2, ": ambiguous redirect \n", 22);
		g_global->exit_status = 1;
		return (1);
	}
	fd = open(strct->file, O_CREAT | O_WRONLY | O_APPEND, 0640);
	if (fd == -1)
		help1_append(strct, fd);
	if (ft_strcmp(strct->file, "/dev/stdout"))
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			write(2, "Error with dup2\n", 17);
			g_global->exit_status = 1;
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	help_handle_redirection(int flag, t_file *current_file)
{
	if (current_file->file_type == IN || current_file->file_type == HER_DOC)
		ft_infile(current_file);
	else if (current_file->file_type == 1)
	{
		flag = 1;
		ft_outfile(current_file);
	}
	else if (current_file->file_type == 3)
	{
		flag = 1;
		ft_append(current_file);
	}
	return (flag);
}

int	handle_redirection(t_minishell *head)
{
	t_file	*current_file;
	int		flag;

	flag = 0;
	if (head->files == NULL && head->next)
	{
		if (dup2(g_global->fd_pipe[1], STDOUT_FILENO) == -1)
			perror("");
		return (0);
	}
	dup2(g_global->save_fd_out, STDOUT_FILENO);
	current_file = head->files;
	while (current_file)
	{
		flag = help_handle_redirection(flag, current_file);
		current_file = current_file->next;
	}
	return (flag);
}

int	redirection(t_minishell *strct)
{
	int	flag;

	flag = handle_redirection(strct);
	if (flag == 0 && strct->next)
		dup2(g_global->fd_pipe[1], STDOUT_FILENO);
	return (0);
}
