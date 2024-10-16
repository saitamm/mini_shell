/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:03:29 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/12 17:25:19 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_space_in(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	str++;
	while (ft_whitespace(str[i]))
	{
		flag = 1;
		i++;
	}
	if (str[i] == '|' || (str[i] == '<' && flag))
		return (1);
	if (str[i] == '>')
		return (1);
	return (0);
}

int	ft_three_in(char *str)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			k++;
		else
			k = 0;
		if (k > 3)
			return (1);
		i++;
	}
	return (0);
}

int	in_norm(char *str, int s_flag, int d_flag)
{
	if (str[0] == '<' && !str[1] && !s_flag && !d_flag)
		return (1);
	else if (str[0] == '<' && ft_space_in(str) && !s_flag && !d_flag)
		return (1);
	else if (str[0] == '<' && ft_three_in(str) && !s_flag && !d_flag)
		return (1);
	else if (str[0] == '<' && str[1] == '|' && !s_flag && !d_flag)
		return (1);
	else if (str[0] == '<' && str[1] == str[0] && str[2] == str[0])
		return (1);
	return (0);
}

int	check_red_in(char *line)
{
	int		i;
	t_flag	l;
	char	*line_t;

	i = 0;
	l.s_quote = 0;
	l.d_quote = 0;
	line_t = ft_strtrim(line, "\n\r\v\f\t ");
	while (line_t[i])
	{
		update_quotes(&l.s_quote, &l.d_quote, line_t[i]);
		if (in_norm(line_t + i, l.s_quote, l.d_quote))
			return (free(line_t), 1);
		if (line_t[i] == '<' && !line_t[i + 1])
			return (free(line_t), 1);
		i++;
	}
	free(line_t);
	return (0);
}
