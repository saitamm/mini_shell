/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:30:13 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/30 10:59:35 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


size_t  len_double_str(char **str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*help_pipe_quote(char *str)
{
	int	i;
	t_flag	b;

	i = 0;
	b.s_quote = 0;
	b.d_quote = 0;
	while (str[i])
	{
		ft_bool_quote(&b.s_quote, &b.d_quote, str[i]);
		if (str[i] == '|' && (b.s_quote || b.d_quote))
			str[i] *= -1;
		i++;
	}
	return (str);
}

char	*help_pipe_quote_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 32 || str[i] > 127)
			str[i] *= -1;
		i++;
	}
	return (str);
}

char	**ft_split_with_pipe(char *line)
{
	char	**str;
	int		i;

	line = help_pipe_quote(line);
	str = ft_split(line, '|');
	i = 0;
	while (str[i])
	{
		help_pipe_quote_2(str[i]);
		i++;
	}
	return (str);
}

