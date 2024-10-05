/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:43:40 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/05 19:11:44 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_open_error(t_file *strct, int infile_fd)
{
	if (access(strct->file, F_OK) != 0)
	{
		hepl_2_ft_infile(strct);
		exit(1);
	}
	else if (access(strct->file, R_OK) != 0)
	{
		hepl_3_ft_infile(strct, infile_fd);
		exit(1);
	}
	hepl_4_ft_infile();
	exit(1);
}

static void	redirect_input(int infile_fd, t_file *strct)
{
	if (ft_strcmp(strct->file, "/dev/stdin"))
	{
		if (dup2(infile_fd, STDIN_FILENO) == -1)
		{
			hepl_5_ft_infile(infile_fd);
			exit(1);
		}
	}
}

int	ft_infile(t_file *strct)
{
	int	infile_fd;

	if (strct->flag == AMB)
	{
		hepl_1_ft_infile(strct);
		exit(1);
	}
	infile_fd = open(strct->file, O_RDONLY);
	if (infile_fd == -1)
		handle_open_error(strct, infile_fd);
	redirect_input(infile_fd, strct);
	close(infile_fd);
	return (0);
}
