/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:09:43 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/22 11:09:55 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strncmp(const char	*str1, const char	*str2, size_t n)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	a1 = (unsigned char *)str1;
	a2 = (unsigned char *)str2;
	i = 0;
	while (i < n && (str1[i] || str2[i]))
	{
		if (a1[i] != a2[i])
			return (a1[i] - a2[i]);
		i++;
	}
	return (0);
}
