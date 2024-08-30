/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:30:13 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/29 21:35:13 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


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
	int	s_flag;
	int	d_flag;

	i = 0;
	s_flag = 0;
	d_flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !d_flag)
			s_flag = !s_flag;
		if (str[i] == '\"' && !s_flag)
			d_flag = !d_flag;
		if (str[i] == '|' && (s_flag || d_flag))
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

