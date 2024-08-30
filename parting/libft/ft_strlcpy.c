/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:04:12 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/29 21:36:16 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_strlcpy(char *str, const char *src, size_t size)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (src[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	while (src[i] != '\0' && i < (size - 1))
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	
	return (j);
}
