/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:51:07 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/12 14:26:17 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_write_in_file(char *name_file, char *d)
{
	int	fd;

	fd = open(name_file, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, 0400);
	if (fd < 0)
	{
		write(2, "failed to open file\n", 20);
		return ;
	}
	if (!d)
	{
		close(fd);
		return ;
	}
	write(fd, d, ft_strlen(d));
	write(fd, "\n", 1);
	close(fd);
}

int	norm_herdoc(char *lim, char *line)
{
	if (!line)
		return (1);
	if (!ft_strcmp(line, lim))
	{
		free(line);
		return (1);
	}
	return (0);
}

char	*create_file_herdoc(char *lim, enum e_token flag_quote)
{
	char	*name_file;
	char	*d;
	char	*line;
	int		flag;
	char	*temp;

	d = NULL;
	flag = 0;
	signal(SIGINT, sig_her_doc);
	name_file = generate_filename();
	while (1)
	{
		line = readline("");
		if (norm_herdoc(lim, line))
			break ;
		temp = help_herdoc(line, flag_quote, &flag, d);
		free(line);
		free(d);
		d = ft_strdup(temp);
		free(temp);
	}
	ft_write_in_file(name_file, d);
	free(d);
	return (name_file);
}
