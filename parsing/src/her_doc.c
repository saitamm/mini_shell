/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:54:51 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/28 10:49:16 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*convert_hex(const char *str, size_t len, const char *base)
{
	char	*name;

	size_t i, j;
	i = 0;
	j = 0;
	name = malloc((len * 2 + 1) * sizeof(char));
	if (!name)
		return (write(2, "failed to allocate memory\n", 27), NULL);
	while (i < len)
	{
		name[j++] = base[(str[i] >> 4) & 0xF];
		name[j++] = base[str[i] & 0xF];
		i++;
	}
	name[j] = '\0';
	return (name);
}

char	*generate_filename(void)
{
	int		fd_random;
	char	*buff;
	char	*name;
	ssize_t	size;
	char	*k;

	fd_random = open("/dev/random", O_RDONLY);
	if (fd_random < 0)
		return (write(2, "failed to open random\n", 22), NULL);
	buff = malloc(12 * sizeof(char));
	if (!buff)
		return (write(2, "failed to allocate memory\n", 27), NULL);
	while (1)
	{
		size = read(fd_random, buff, 11);
		if (size < 0)
		{
			return (write(2, "failed to read number of bytes\n", 29), NULL);
		}
		buff[11] = '\0';
		k = convert_hex(buff, 11, "0123456789abcdef");
		name = ft_strjoin("/tmp/.", k);
		free(k);
		if (access(name, F_OK))
			break ;
	}
	close(fd_random);
	return (name);
}

int	need_expand_her_doc(char *str, int *pos, int flag)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !flag)
		{
			*pos = i;
			return (1);
		}
		i++;
	}
	return (0);
}
char	*create_file_herdoc(char *lim, enum e_token flag_quote)
{
	char	*name_file;
	char	*d;
	char	*line;
	char	*line_exp;
	bool	flag;
	int		i;
				int k;
	int		fd;

	i = 0;
	d = NULL;
	flag = false;
	name_file = generate_filename();
	while (1)
	{
		line = readline(">");
		if (!ft_strncmp(line, lim, ft_strlen(line)))
			break ;
		if (!flag)
		{
			line_exp = ft_strdup(line);
			if (flag_quote != Q_HER)
			{
				while ((k = need_expand_her_doc(line_exp, &i,0)))
					line_exp = expand_str(line_exp, i);
			}
			flag = !flag;
		}
		else
		{
			d = ft_strjoin(d, "\n");
			line_exp = ft_strdup(line);
			if (flag_quote != Q_HER)
			{
				while (need_expand_her_doc(line_exp, &i,0))
					line_exp = expand_str(line_exp, i);
			}
		}
		d = ft_strjoin(d, line_exp);
	}
	fd = open(name_file, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, 0400);
	if (fd < 0)
		return (write(2, "failed to open file\n", 21), NULL);
	if (!d)
		return (close(fd), name_file);
	write(fd, d, ft_strlen(d));
	write(fd, "\n", 1);
	close(fd);
	free(d);
	return (name_file);
}
