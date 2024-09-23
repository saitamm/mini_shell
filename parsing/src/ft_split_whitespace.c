/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:08:51 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/23 12:57:23 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_len(const char *s)
{
	int	i;
	int	len;
	int	flag;

	i = 0;
	len = 0;
	flag = 0;
	while (s[i])
	{
		if (ft_whitespace(s[i]))
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			len++;
		}
		i++;
	}
	return (len);
}

static int	sub_len(const char *s)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i] && !ft_whitespace(s[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static char	*ft_cpy(const char *s)
{
	char	*d;
	int		i;
	int		w;

	i = 0;
	w = sub_len(s);
	d = (char *)malloc(sizeof(char) * (w + 1));
	if (!d)
		return (NULL);
	while (s[i] && i < w)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	**ft_split_whitesp(const char *s)
{
	char	**str;
	int		i;
	int		cw;

	if (!s)
		return (NULL);
	cw = ft_len(s);
	str = (char **)malloc((cw + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (i < cw)
	{
		while (*s && ft_whitespace(*s))
			s++;
		str[i] = ft_cpy(s);
		if (!str[i++])
		{
			ft_free(str, i);
			return (NULL);
		}
		s = s + sub_len(s);
	}
	str[i] = NULL;
	// free((char *	)s);
	return (str);
}
