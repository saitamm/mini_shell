/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:54:51 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/06 11:29:45 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*convert_hex(const char *str, size_t len, const char *base)
{
	char	*name;
	size_t	i;
	size_t	j;

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
			return (write(2, "failed to read number of bytes\n", 29), NULL);
		buff[11] = '\0';
		k = convert_hex(buff, 11, "0123456789abcdef");
		name = ft_strjoin("/tmp/.", k);
		free(k);
		if (access(name, F_OK))
			break ;
	}
	return (free(buff), close(fd_random), name);
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

char	*expand_herdoc(char *line, enum e_token flag_quote)
{
	char	*line_exp;
	char	*exp;
	int		pos;

	line_exp = ft_strdup(line);
	if (flag_quote != Q_HER)
	{
		while (need_expand_her_doc(line_exp, &pos, 0))
		{
			exp = expand_str(line_exp, pos);
			free(line_exp);
			line_exp = ft_strdup(exp);
			free(exp);
		}
	}
	return (line_exp);
}

char	*help_herdoc(char *line, enum e_token flag_quote, int *flag, char *d)
{
	char	*line_exp;
	char	*d_r;

	if (!(*flag))
	{
		line_exp = expand_herdoc(line, flag_quote);
		(*flag) = !(*flag);
	}
	else
	{
		line_exp = expand_herdoc(line, flag_quote);
		d = ft_strjoin(d, "\n");
	}
	d_r = ft_strjoin(d, line_exp);
	free(d);
	free(line_exp);
	return (d_r);
}
