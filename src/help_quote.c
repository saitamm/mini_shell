/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:13:57 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/02 10:31:45 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	update_quotes(bool *s, bool *d, char c)
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
	printf("**********%s\n", str);
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
