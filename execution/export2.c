/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:09:53 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/30 18:04:33 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_export_unset_args(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] <= 'z' && str[i] >= 'a') || (str[i] <= 'Z' && str[i] >= 'A')
			|| (str[i] <= '9' && str[i] >= '0') || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	find_key(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_change_key_value(char *key, char *value)
{
	t_env	*head;
	char	*new_value;

	head = g_global->env;
	while (g_global->env)
	{
		if (ft_strcmp(key, g_global->env->key) == 0)
		{
			if (g_global->separator == 1)
			{
				new_value = malloc(ft_strlen(g_global->env->value)
						+ ft_strlen(value) + 1);
				if (new_value == NULL)
					return ;
				ft_strcpy(new_value, g_global->env->value);
				ft_strcat(new_value, value);
				free(g_global->env->value);
				g_global->env->value = new_value;
			}
			else
			{
				new_value = malloc(ft_strlen(value) + 1);
				if (new_value == NULL)
					return ;
				ft_strcpy(new_value, value);
				free(g_global->env->value);
				g_global->env->value = new_value;
			}
			break ;
		}
		else
			g_global->env = g_global->env->next;
	}
	g_global->env = head;
}

void	ft_check_key(char *str)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		key = get_key(str);
		value = equal_sign + 1;
		if (ft_check_export_unset_args(key) == 0)
			return ;
		if (find_key(g_global->env, key) == 0 && key && value)
			add_to_list(&g_global->env, key, value);
		else
			ft_change_key_value(key, value);
	}
	else
	{
		key = ft_strdup(str);
		if (key)
			add_to_list(&g_global->env, key, "");
	}
	free(key);
}
