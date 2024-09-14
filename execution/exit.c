/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:56:12 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/14 09:45:51 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int isanumvalue(char *str)
{
	int count;
	size_t number;
	int negative;

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

long ft_atoll(char *c)
{
	int i;

	int signe;
	long result;

	i = 0;
	signe = 1;
	result = 0;
	// while ((c[i] <= 13 && c[i] >= 9) || c[i] == 32)
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
	// return (result);
}

// void ft_exit(char **cmd)
// {
// 	if (!cmd)
// 		return;
// 	if (cmd[1] && cmd[2] == NULL)
// 	{
// 		if (isanumvalue(cmd[1]))
// 			exit(ft_atoll(cmd[1]));
// 		else
// 			printf("exit \nbash: exit: %s: numeric argument required\n", cmd[1]);
// 		exit(2);
// 	}
// 	else
// 		printf("exit \nbash: exit: too many arguments\n");
// }

void ft_exit(char **cmd)
{
	if (!cmd || !cmd[1])
	{
		printf("soumaya\n");
		exit(0);
	}
	if (isanumvalue(cmd[1]))
	{
		if (cmd[1])
			exit(ft_atoll(cmd[1]));
		g_global->exit_status = 1;
		printf("exit \nbash: exit: too many arguments\n");
	}
	else
	{
		printf("exit \nbash: exit: %s: numeric argument required\n", cmd[1]);
		exit(2);
	}
}
