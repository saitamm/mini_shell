/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:13:05 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/05 04:21:16 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	help_add_to_env(char *value, char *str, char *key, char *tmp)
{
	value = ft_substr(str + ft_strlen(key) + 2, 0, ft_strlen(str)
			- ft_strlen(key) - 2);
	if (find_key(g_global->env, key) == 0)
	{
		add_to_list(&g_global->env, key, value);
		free(value);
	}
	else
	{
		tmp = ft_strjoin(help_expand(key), value);
		ft_lstremove(key);
		add_to_list(&g_global->env, key, tmp);
		free(value);
		free(tmp);
	}
}

void	add_to_env(char *str, char *key)
{
	char	*value;
	char	*tmp;

	value = NULL;
	tmp = NULL;
	if (str[ft_strlen(key)] == '=')
	{
		value = ft_substr(str + ft_strlen(key) + 1, 0, ft_strlen(str)
				- ft_strlen(key) - 1);
		if (find_key(g_global->env, key) == 0)
		{
			add_to_list(&g_global->env, key, value);
			free(value);
		}
		else
		{
			ft_change_key_value(key, value);
			free(value);
		}
	}
	else if (str[ft_strlen(key)] == '+')
		help_add_to_env(value, str, key, tmp);
	else if (find_key(g_global->env, key) == 0)
		add_to_list(&g_global->env, key, NULL);
}

void	add_key_export(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || str[i] == '+')
			break ;
		i++;
	}
	key = ft_substr(str, 0, i);
	{
		if (!ft_strcmp(key, "PATH"))
			g_global->flag_env = 1;
		add_to_env(str, key);
	}
	free(key);
}

void	ft_export(t_minishell *strct)
{
	int	i;

	i = 1;
	if (strct->cmd[1] == NULL)
		print_export();
	else
	{
		while (strct->cmd[i])
		{
			if (check_error_export(strct->cmd[i]))
			{
				i++;
				continue ;
			}
			add_key_export(strct->cmd[i]);
			i++;
		}
	}
}
