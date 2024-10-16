/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:16:07 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/12 17:23:25 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quote(char *line)
{
	int	i;
	int	s_flag;
	int	d_flag;

	i = 0;
	s_flag = 0;
	d_flag = 0;
	if (line[0] == '|')
		return (1);
	while (line[i])
	{
		if (line[i] == '\"' && !s_flag)
			d_flag = !d_flag;
		if (line[i] == '\'' && !d_flag)
			s_flag = !s_flag;
		i++;
	}
	if (s_flag == 1 || d_flag == 1)
		return (1);
	return (0);
}

int	check_bracket(char *str)
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
		if ((str[i] == '(' || str[i] == ')') && !s_flag && !d_flag)
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe(char *line)
{
	char	*line_t;
	int		i;

	line_t = ft_strtrim(line, "\n\r\v\f\t ");
	if (line_t[0] == '|')
		return (free(line_t), 1);
	i = 0;
	while (line_t[i])
	{
		if ((line_t[i] == '|' && !line_t[i + 1]))
		{
			free(line_t);
			return (1);
		}
		i++;
	}
	free(line_t);
	return (0);
}

int	chech_pipe_2(char *line)
{
	t_flag	d;
	int		i;
	char	*line_t;

	i = 0;
	line_t = ft_strtrim(line, "\n\r\v\f\t ");
	d.s_quote = false;
	d.d_quote = false;
	while (line_t[i])
	{
		update_quotes(&d.s_quote, &d.d_quote, line_t[i]);
		if (line_t[i] != '|' && !d.s_quote && !d.d_quote)
			break ;
		i++;
	}
	while (ft_whitespace(line_t[i]))
		i++;
	if (line_t[i] == '|')
		return (free(line_t), 1);
	return (free(line_t), 0);
}

int	parce_error(char *line)
{
	if (check_pipe(line))
		return (synt_error(ERROR, '|') || chech_pipe_2(line));
	if (check_quote(line))
		return (synt_error(ERROR, '"'));
	if (check_bracket(line))
		return (synt_error(ERROR, '('));
	if (check_red_out(line))
		return (synt_error(ERROR, '>'));
	if (check_red_in(line))
		return (synt_error(ERROR, '<'));
	return (0);
}
