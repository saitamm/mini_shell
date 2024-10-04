/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:17:14 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/04 11:01:52 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_infile(t_file *strct)
{
	int infile_fd;

	if (strct->flag == AMB)
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
	infile_fd = open(strct->file, O_RDONLY);
	if (infile_fd == -1)
	{
		if (access(strct->file, F_OK) != 0)
		{
			write(2, "Minishell:", 11);
			perror(strct->file);
			close(g_global->save_fd_int);
            close(g_global->save_fd_out);
			close(g_global->fd_pipe[1]);
			close(g_global->fd_pipe[0]);
			free_minishell(&g_global->strct);
			free(g_global->pid);
			ft_free_global();
			free(g_global);
			// ft_free_global();
			exit(1);
		}
		else if (access(strct->file, R_OK) != 0)
		{
			write(2, "Minishell:", 11);
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
			exit(1);
		}
		perror("Error opening file\n");
		// ft_free_global();
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
            close(g_global->save_fd_out);
			close(g_global->fd_pipe[1]);
			close(g_global->fd_pipe[0]);
		ft_free_global();
		free(g_global);
		exit(1);
	}
	if (ft_strcmp(strct->file, "/dev/stdin"))
	{
		if (dup2(infile_fd, STDIN_FILENO) == -1)
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
			exit(1);
		}
	}
	close(infile_fd);
	return (0);
}

int ft_outfile(t_file *strct)
{
	int outfile_fd;

	if (strct->flag == AMB)
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
	outfile_fd = open(strct->file, O_CREAT | O_TRUNC | O_WRONLY, 0640);
	if (outfile_fd == -1)
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
int ft_append(t_file *strct)
{
	int fd;

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
	{
		write(2, "Minishell:", 11);
		perror(strct->file);
		g_global->exit_status = 1;
		close(fd);
		ft_free_global();
		exit(g_global->exit_status);
	}
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
		return (0);
	}
	return (0);
}

int redirection(t_minishell *strct)
{
	t_minishell *head = strct;
	t_file *current_file;
	if (head->files == NULL && head->next && head)
	{
		if (dup2(g_global->fd_pipe[1], STDOUT_FILENO) == -1)
			perror("");
		return (0);
	}
	dup2(g_global->save_fd_out, STDOUT_FILENO);
	int flag;
	flag = 0;
	current_file = head->files;
	while (current_file)
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
		current_file = current_file->next;
	}
	if (flag == 0 && strct->next)
		dup2(g_global->fd_pipe[1], STDOUT_FILENO);
	return (0);
}
