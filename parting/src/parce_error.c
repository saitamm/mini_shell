/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:16:07 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/29 21:34:57 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_quote(char *line)
{
	int i;
	int s_flag;
	int d_flag;

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

int	check_logical(char *str)
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
		if ((str[i] == '|' && str[i + 1] == '|') && !s_flag && !d_flag)
			return (1);
		if ((str[i] == '&' &&  str[i + 1] == '&') && !s_flag && !d_flag)
			return (1);
		i++;
	}
	return (0);
}

int    parce_error(char *line)
{
	if (check_quote(line))
		return (synt_error(ERROR));
	if (check_bracket(line) )
		return (synt_error(ERROR));
	if (check_logical(line))
		return (synt_error(ERROR));
	if (check_red_out(line))
		return (synt_error(ERROR));
	if (check_red_in(line))
		return (synt_error(ERROR));
	return (0);
	
}
