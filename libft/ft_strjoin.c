/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:09:52 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/13 11:07:44 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_cpy(const char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*d;
	int		len1;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1) + ft_strlen(s2);
	d = (char *)malloc((len1 + 1) * sizeof(char const));
	if (!d)
		return (NULL);
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		d[i + j] = s2[j];
		j++;
	}
	d[i + j] = '\0';
	return (d);
}

char	*ft_strjoin(char  *s1, char *s2, int f)
{
	char	*d;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	d = ft_cpy(s1, s2);
	if (f == 2)
		{
			free(s1);
			free(s2);
		}
	else if (f == 1)
		free(s1);
	else if (f == 0)
		free(s2);
	return (d);
}
