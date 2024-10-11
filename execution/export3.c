/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 04:06:54 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/11 10:05:34 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_swaped(t_env *a, t_env *b)
{
	char *tmp_key;
	char *tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void ft_list_sort(t_env **env)
{
	t_env *tmp;
	int i;

	if (!env || !*env)
		return;
	i = 1;
	while (i)
	{
		i = 0;
		tmp = *env;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				ft_swaped(tmp, tmp->next);
				i = 1;
			}
			tmp = tmp->next;
		}
	}
}

void print_export(void)
{
	t_env *tmp;

	tmp = g_global->env;
	ft_list_sort(&tmp);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") == 0)
			tmp = tmp->next;
		else
		{
			if (!tmp->value)
				printf("declare -x %s\n", tmp->key);
			else if (tmp->value && tmp->key)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
}

void error_export(char *str, char *error)
{
	int i;
	char *key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	(void)error;
	key = ft_substr(str, 0, i);
	write(2, "Minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	g_global->exit_status = 1;
	free(key);
}

int check_error_export(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[0] != '_')
		return (error_export(str, "not a valid identifier\n"), 1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (error_export(str, "not a valid identifier\n"), 1);
		i++;
	}
	return (0);
}
