/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:13:57 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/28 15:54:41 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			str[i] *= (-1);
		i++;
	}
	return (str);
}

int	nomber_quote_dollar(char *str)
{
	int		i;
	t_flag	b;
	int		count;

	i = 0;
	count = 0;
	b.s_quote = false;
	b.d_quote = false;
	while (str[i])
	{
		update_quotes(&b.s_quote, &b.d_quote, str[i]);
		if ((!b.s_quote && !b.d_quote) && (str[i] == '\'' || str[i] == '\"')
			&& str[i + 1])
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

int	help_remove_quote(char *str, t_flag b)
{
	if (((!b.s_quote && !b.d_quote) && (str[0] == '\'' || str[0] == '\"')))
		return (1);
	else if (!b.d_quote && str[0] == '\'')
		return (1);
	else if (!b.s_quote && str[0] == '\"')
		return (1);
	return (0);
}

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	char	*file;
	t_flag	b;

	b.s_quote = false;
	b.d_quote = false;
	file = malloc((ft_strlen(str) - nomber_quote_dollar(str) + 1)
			* sizeof(char));
	if (!file)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		update_quotes(&b.s_quote, &b.d_quote, str[i]);
		if (!help_remove_quote(str + i, b))
		{
			file[j] = str[i];
			j++;
		}
		i++;
	}
	file[j] = '\0';
	return (file);
}
