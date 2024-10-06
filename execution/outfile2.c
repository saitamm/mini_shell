/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:03:33 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 12:07:06 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	help_1_ft_outfile_built(t_file *strct)
{
	write(2, "Minishell:", 11);
	write(2, strct->file, ft_strlen(strct->file));
	write(2, ": ambiguous redirect\n", 22);
	g_global->exit_status = 1;
	return (1);
}

int	ft_outfile_built(t_file *strct)
{
	int	outfile_fd;

	if (strct->flag == AMB)
	{
		help_1_ft_outfile_built(strct);
		return (1);
	}
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

int	ft_append_built(t_file *strct)
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
