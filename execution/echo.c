/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 01:02:07 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/05 03:50:36 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_find_in_env(char *search_key)
{
	while (g_global->env != NULL)
	{
		if (strcmp(g_global->env->key, search_key) == 0)
			return ;
		g_global->env = g_global->env->next;
	}
}

int	check_n(const char *s)
{
	int	i;

	i = 1;
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}

int	ft_echo(char **str)
{
	int	newline;

	g_global->j = 1;
	newline = 1;
	while (str[g_global->j] && str[g_global->j][0] == '-'
		&& check_n(str[g_global->j]))
	{
		newline = 0;
		g_global->j++;
	}
	while (str[g_global->j])
	{
		g_global->i = 0;
		while (str[g_global->j][g_global->i])
		{
			write(1, &str[g_global->j][g_global->i], 1);
			g_global->i++;
		}
		if (str[g_global->j + 1])
			write(1, " ", 1);
		g_global->j++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
