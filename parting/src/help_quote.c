/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:13:57 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/30 13:22:36 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	ft_bool_quote(bool *s, bool *d, char c)
{
	if (c == '\'' && !(*d))
			(*s) = !(*s);
	if (c == '\"' && !(*s))
			(*d) = !(*d);
}

char	*help_quote_exp(char *str)
{	
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			str[i] *= (-1);
		i++;
	}
	return (str);
}

char	*remove_quote(char *str)
{
	int		i;
	char	*r_str;

	r_str = malloc((ft_strlen(str) - 2 + 1) * sizeof(char));
	if (!r_str)
		return (NULL);
	i = 1;
	while (str[i+ 1])
	{
		r_str[i - 1] = str[i];
		i++;
	}
	r_str[i - 1] = '\0';
	free(str);
	return (r_str);
}
