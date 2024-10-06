/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:52:20 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 10:51:01 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*help_get_key(int separator_pos, char *key, char *s, int j)
{
	if (separator_pos == -1)
		return (NULL);
	key = malloc((sizeof(char) * separator_pos) + 1);
	if (!key)
		return (NULL);
	while (j < separator_pos)
	{
		key[j] = s[j];
		j++;
	}
	key[separator_pos] = '\0';
	return (key);
}

char	*get_key(char *s)
{
	int		separator_pos;
	char	*key;

	g_global->i = 0;
	g_global->j = 0;
	key = NULL;
	separator_pos = -1;
	while (s[g_global->i])
	{
		if (s[g_global->i] == '=')
		{
			separator_pos = g_global->i;
			if (g_global->i > 0 && s[g_global->i - 1] == '+')
			{
				g_global->separator = 1;
				separator_pos--;
			}
			else
				g_global->separator = 0;
			break ;
		}
		g_global->i++;
	}
	key = help_get_key(separator_pos, key, s, g_global->j);
	return (key);
}

void	ft_set_underscor_value(void)
{
	t_env	*tmp;

	tmp = g_global->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup("/usr/bin/env");
			return ;
		}
		tmp = tmp->next;
	}
}

void	hepl_parse_env_var(char **env_var, int i)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = NULL;
	key = NULL;
	value = NULL;
	equal_sign = ft_strchr(env_var[i], '=');
	if (equal_sign)
	{
		key = get_key(env_var[i]);
		value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
		if (!key || !value)
			return ;
		add_to_list(&g_global->env, key, value);
		free(key);
		free(value);
	}
}

void	parse_env_var(char **env_var)
{
	int	i;

	i = 0;
	if (!env_var[0])
	{
		env_manuel();
		return ;
	}
	if (!env_var)
		return ;
	while (env_var[i])
	{
		hepl_parse_env_var(env_var, i);
		i++;
	}
	ft_set_underscor_value();
}
