/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:01:51 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/19 20:31:52 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_red_out(char *str)
{
	int		i;
	t_flag	f;

	i = 0;
	f.s_quote = 0;
	f.d_quote = 0;
	while (str[i])
	{
		update_quotes(&f.s_quote, &f.d_quote, str[i]);
		if (str[i] == '>' && (!str[i + 1] || ft_space_out(str + i)
				|| ft_three_out(str + i) || ft_pipe_out(str + i)) && !f.s_quote
			&& !f.d_quote)
			return (1);
		if (!ft_whitespace(str[i]) && str[i] == '>' && !f.s_quote && !f.d_quote)
			return (1);
		i++;
	}
	return (0);
}

int	ft_pipe_out(char *str)
{
	if (str[0] == '>' && str[1] == '|')
		return (1);
	return (0);
}

int	ft_three_out(char *str)
{
	int	i;
	int	k;
	int	flag;

	k = 0;
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '>')
			k++;
		else
			k = 0;
		if (k > 2)
			return (1);
		i++;
	}
	return (0);
}

int	ft_space_out(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	str++;
	while (whitespace(str[i]))
	{
		i++;
		flag = 1;
	}
	if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && flag)
		return (1);
	return (0);
}