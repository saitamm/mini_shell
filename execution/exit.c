/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:56:12 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/04 12:03:57 by sait-amm         ###   ########.fr       */
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

int ft_exit(char **cmd)
{
	if (!cmd || !cmd[1])
	{
		int ex = g_global->exit_status;
		if (ft_lstsize_minishell(g_global->strct))
		{
			close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		close(g_global->fd_pipe[1]);
		close(g_global->fd_pipe[0]);
		}
		free_minishell(&g_global->strct);
		free_list(&g_global->env);
		if (g_global->pwd)
			free(g_global->pwd);
		if (g_global->oldpwd)
			free(g_global->oldpwd);
		if (g_global->underscore)
			free(g_global->underscore);
		if (g_global->pid)
			free(g_global->pid);
		free(g_global);
		exit(ex);
	}
	if (isanumvalue(cmd[1]))
	{
		if (!cmd[2])
		{
			int ex = ft_atoll(cmd[1]);
			free_minishell(&g_global->strct);
			free_list(&g_global->env);
			close(g_global->save_fd_int);
            close(g_global->save_fd_out);
			if (g_global->pwd)
				free(g_global->pwd);
			if (g_global->oldpwd)
				free(g_global->oldpwd);
			if (g_global->underscore)
				free(g_global->underscore);
			if (g_global->pid)
				free(g_global->pid);
			free(g_global);
			exit(ex);
		}
		write(2, "exit \nMinishell : exit: too many arguments\n", 44);
		return 1;
	}
	else
	{
		write(2, "exit \nMinishell: exit: ", 24);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": numeric argument required\n", 29);
		if (ft_lstsize_minishell(g_global->strct))
		{
			close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		close(g_global->fd_pipe[1]);
		close(g_global->fd_pipe[0]);
		}
		free_minishell(&g_global->strct);
		close(g_global->save_fd_int);
            close(g_global->save_fd_out);
		free_list(&g_global->env);
		if (g_global->pwd)
			free(g_global->pwd);
		if (g_global->oldpwd)
			free(g_global->oldpwd);
		if (g_global->underscore)
			free(g_global->underscore);
		if (g_global->pid)
			free(g_global->pid);
		free(g_global);
		exit(2);
	}
	return 0;
}
