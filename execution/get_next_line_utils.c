/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:59:50 by lai-elho          #+#    #+#             */
/*   Updated: 2024/01/21 17:52:51 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t	ft_strlen(char *c)
// {
// 	size_t	size;

// 	size = 0 ;
// 	while (c[size])
// 		size++;
// 	return (size);
// }

// char	*ft_strdup(char *src)
// {
// 	int		len;
// 	char	*dest;
// 	int		i;

// 	i = 0;
// 	len = ft_strlen(src);
// 	dest = malloc((len + 1) * sizeof(char));
// 	if (!dest)
// 		return (NULL);
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*s;

// 	if (s1 == NULL && s2 == NULL)
// 		return (NULL);
// 	if (s2 == NULL)
// 		return (ft_strdup((char *)s1));
// 	if (s1 == NULL)
// 		return (ft_strdup((char *)s2));
// 	i = -1;
// 	j = -1;
// 	s = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!s)
// 		return (NULL);
// 	while (s1[++i])
// 		s[i] = s1[i];
// 	while (s2[++j])
// 		s[i + j] = s2[j];
// 	s[i + j] = '\0';
// 	free(s1);
// 	return (s);
// }

size_t	ft_len_newline(const char *c)
{
	size_t	len ;

	len = 0 ;
	while (c[len] && c[len] != '\n')
		len++;
	if (c[len] == '\n')
		len++;
	return (len);
}
