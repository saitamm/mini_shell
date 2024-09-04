/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/04 14:59:36 by lai-elho         ###   ########.fr       */
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
    if(cmd[1])
    {
        if(isanumvalue(cmd[1]))
            exit(atoll(cmd[1])); // don't forget to change atoll to ft_....
        else
            printf("eroooooor]\n");
    }else
        exit(0);
        
}

void ft_execution(t_minishell *strct, t_execution *exec)
{
    if(ft_strcmp(strct->cmd[0], "pwd") == 0)
        ft_pwd();
    if(ft_strcmp(strct->cmd[0], "env") == 0)
    {
        t_env *temp = g_global->env;
        print_env(temp);
    }
    if(ft_strcmp(strct->cmd[0], "echo") == 0)
        ft_echo(strct->cmd);
    if(ft_strcmp(strct->cmd[0], "cd") == 0)
        ft_cd(strct->cmd[1]);
    if(ft_strcmp(strct->cmd[0], "unset") == 0)
        unset(exec->av);
    if(ft_strcmp(strct->cmd[0], "export") == 0)
        ft_export(exec);
    if(ft_strcmp(strct->cmd[0], "exit") == 0)
        ft_exit(strct->cmd);
}