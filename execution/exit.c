/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:56:12 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/12 18:12:05 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	isanumvalue(char *str)
{
	int		count;
	size_t	number;
	int		negative;

	negative = 0;
	count = 0;
	number = 0;
	while (*str == ' ' || *str == '	')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = 1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		number = number * 10 + (*str++ - 48);
		count++;
	}
	if (count >= 20 || number - negative > __LONG_MAX__)
		return (0);
	return (1);
}

long	ft_atoll(char *c)
{
	int		i;
	int		signe;
	long	result;

	i = 0;
	signe = 1;
	result = 0;
	while (c[i] == ' ' || c[i] == '	')
		i++;
	if (c[i] == '+' || c[i] == '-')
	{
		if (c[i] == '-')
			signe = -1;
		i++;
	}
	while (c[i] <= '9' && c[i] >= '0')
	{
		result = result * 10 + (c[i] - '0');
		i++;
	}
	return (result * signe);
}

int	ft_exit(char **cmd)
{
	int	ex;

	if (!cmd || !cmd[1])
	{
		ex = g_global->exit_status;
		ft_free_1_in_exit();
		exit(ex);
	}
	if (isanumvalue(cmd[1]))
	{
		if (!cmd[2])
		{
			ex = ft_atoll(cmd[1]);
			ft_free_2_in_exit();
			exit(ex);
		}
		write(2, "exit \nMinishell : exit: too many arguments\n", 43);
		return (1);
	}
	else
	{
		ft_free_3_in_exit(cmd);
		exit(2);
	}
	return (0);
}
