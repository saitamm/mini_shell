/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 23:35:46 by lai-elho          #+#    #+#             */
/*   Updated: 2024/01/23 00:25:29 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_new_line(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read(int fd, char *str)
{
	char	*buff;
	ssize_t	size;

	size = 0;
	buff = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (free(str), NULL);
	while (!find_new_line(str))
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size < 0)
			return (free(buff), NULL);
		if (size == 0)
			return (free(buff), str);
		buff[size] = '\0';
		str = ft_strjoin(str, buff);
	}
	return (free(buff), str);
}

char	*ft_result(char *str)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	if (str == NULL)
		return (NULL);
	len = ft_len_newline(str);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (str[i] != '\n' && str[i])
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		res[i] = '\n';
		res[i + 1] = '\0';
	}
	else
		res[i] = '\0';
	return (res);
}

char	*ft_save(char *str)
{
	char	*res;
	size_t	len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		if (str[i + 1] == '\0')
			return (free(str), NULL);
		len = ft_strlen(str) - ft_len_newline(str);
		res = malloc(sizeof(char) * (len + 1));
		if (!res)
			return (0);
		while (str[++i])
			res[j++] = str[i];
		res[len] = '\0';
		return (free(str), res);
	}
	return (free(str), NULL);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*res;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	str = ft_read(fd, str);
	res = ft_result(str);
	str = ft_save(str);
	return (res);
}
