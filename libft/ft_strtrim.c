/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:02:58 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/30 10:59:53 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int			s;
	int			i;
	char const	*str;

	if (!s1 || !set)
		return (NULL);
	s = 0;
	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[s]) && s <= i)
		s++;
	if (s > i)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[i]) && i >= 0)
		i--;
	str = malloc((i - s + 2) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy((char *)str, (char *)&s1[s], i - s + 2);
	// free(s1);
	return ((char *)str);
}
