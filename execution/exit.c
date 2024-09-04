/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:56:12 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/03 23:46:31 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int	isanumvalue(char *str)
// {
// 	int		count;
// 	size_t	number;
// 	int		negative;

// 	negative = 0;
// 	count = 0;
// 	number = 0;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			negative = 1;
// 		str++;
// 	}
// 	while (*str)
// 	{
// 		if (*str < '0' || *str > '9')
// 			return (0);
// 		number = number * 10 + (*str++ - 48);
// 		count++;
// 	}
// 	if (count >= 20 || number - negative > __LONG_MAX__)
// 		return (0);
// 	return (1);
// }

// void	initialize_i(int i[2])
// {
// 	i[0] = 0;
// 	i[1] = 0;
// }

// void	ft_exit(char **cmd)
// {
// 	int	exit_st;
// 	int	i[2];

// 	exit_st = stat_handler(0, 0);
// 	initialize_i(i);
// 	while (cmd[i[0]])
// 		i[0]++;
// 	ft_write("exit", 2, 1);
// 	if (cmd[1] && !isanumvalue(cmd[1]))
// 	{
// 		ft_write("minishell: exit: ", 2, 0);
// 		ft_write(cmd[1], 2, 0);
// 		ft_write(": numeric argument required", 2, 1);
// 		exit_st = 2;
// 	}
// 	else if (i[0] > 2)
// 	{
// 		ft_write("minishell: exit: too many arguments", 2, 1);
// 		i[1] = 1;
// 		stat_handler(1, 1);
// 	}
// 	else if (cmd[1] && i[0] <= 2)
// 		exit_st = ft_atoi(cmd[1]);
// 	if (!i[1])
// 		exit(exit_st);
// }