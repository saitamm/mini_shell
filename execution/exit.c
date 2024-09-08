/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:56:12 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/08 14:04:42 by lai-elho         ###   ########.fr       */
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

void ft_exit(char **cmd)
{
    if(!cmd)
        return;
    if(cmd[1] && cmd[2] == NULL)
    {	
        if(isanumvalue(cmd[1]) )
            exit(atoll(cmd[1])); // don't forget to change atoll to ft_....
        else
            printf("exit \nbash: exit: %s: numeric argument required\n",cmd[1]);
			exit(2);
    }else
		printf("exit \nbash: exit: too many arguments\n");
}