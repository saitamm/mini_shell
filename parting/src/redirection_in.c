/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:03:29 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/30 13:22:51 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_space_in(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag =0;
	str++;
	while (ft_whitespace(str[i]))
	{
		flag=1;
		i++;
	}
	if (str[i] == '|' || (str[i] == '<' && flag))
		return (1);
	return (0);
}

int	ft_three_in(char *str)
{
	int	i;
	int	k;
	int	flag;

	k = 0;
	i = 0;
	flag = 0;
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
		return(1);
	else if (str[0] == '<' && ft_space_in(str) && !s_flag && !d_flag)
		return (1);
	else if (str[0] == '<' && ft_three_in(str) && !s_flag && !d_flag)
		return (1);
	else if (str[0] == '<' && str[1] == '|' && !s_flag && !d_flag)
		return (1);
	return (0);
}
int	check_red_in(char *str)
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
		if (in_norm(str+i, s_flag, d_flag))		
			return (1);
		i++;
	}
	return (0);
}



