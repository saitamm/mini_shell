/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:02:16 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 11:15:51 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_ambiguous_redirect(t_file *strct)
{
	if (strct->flag == AMB)
	{
		write(2, "Minishell:", 11);
		write(2, strct->file, ft_strlen(strct->file));
		write(2, ": ambiguous redirect\n", 22);
		g_global->exit_status = 1;
		return (1);
	}
	return (0);
}

int	open_infile(t_file *strct)
{
	int	infile_fd;

	infile_fd = open(strct->file, O_RDONLY);
	if (infile_fd == -1)
	{
		if (access(strct->file, F_OK) != 0)
		{
			write(2, "Minishell:", 11);
			perror(strct->file);
			g_global->exit_status = 1;
		}
		else if (access(strct->file, R_OK) != 0)
		{
			write(2, "Minishell:", 11);
			perror(strct->file);
			g_global->exit_status = 1;
		}
		else
			perror("Error opening file\n");
	}
	return (infile_fd);
}

int	ft_infile_built(t_file *strct)
{
	int	infile_fd;

	if (handle_ambiguous_redirect(strct))
		return (1);
	infile_fd = open_infile(strct);
	if (infile_fd == -1)
		return (1);
	if (ft_strcmp(strct->file, "/dev/stdin"))
	{
		if (dup2(infile_fd, STDIN_FILENO) == -1)
		{
			perror("Error in dup2\n");
			g_global->exit_status = 1;
			close(infile_fd);
			return (1);
		}
	}
	close(infile_fd);
	return (0);
}

int	handle_file_redirection(t_file *current_file)
{
	if (current_file->file_type == IN || current_file->file_type == HER_DOC)
	{
		if (ft_infile_built(current_file))
			return (1);
	}
	else if (current_file->file_type == 1)
	{
		if (ft_outfile_built(current_file))
			return (1);
	}
	else if (current_file->file_type == 3)
	{
		if (ft_append_built(current_file))
			return (1);
	}
	return (0);
}

int	redirection_buils(t_minishell *strct)
{
	t_minishell	*head;
	t_file		*current_file;

	head = strct;
	current_file = head->files;
	while (current_file)
	{
		if (handle_file_redirection(current_file))
			return (1);
		current_file = current_file->next;
	}
	head = head->next;
	return (0);
}
