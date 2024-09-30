/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:13:05 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/30 17:19:31 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_swaped(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	ft_list_sort(t_env **env)
{
	t_env	*tmp;
	int		i;

	if (!env || !*env)
		return ;
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

void	print_export(void)
{
	t_env	*tmp;

	tmp = g_global->env;
	ft_list_sort(&tmp);
	while (tmp)
	{
		if (!tmp->value)
			printf("declare -x %s\n", tmp->key);
		else if (tmp->value && tmp->key)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	error_export(char *str, char *error, int flag)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	(void)error;
	key = ft_substr(str, 0, i);
	write(2, "Minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	g_global->exit_status = flag;
}

int	check_error_export(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		return (error_export(str, "not a valid option \n", 2), 1);
	if (!ft_isalpha(str[i]) && str[0] != '_')
		return (error_export(str, "not a valid identifier\n", 1), 1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (error_export(str, "not a valid identifier\n", 1), 1);
		i++;
	}
	return (0);
}

void	add_to_env(char *str, char *key)
{
	char	*value;
	char	*tmp;

	if (str[ft_strlen(key)] == '=')
	{
		value = ft_substr(str + ft_strlen(key) + 1, 0, ft_strlen(str)
				- ft_strlen(key) - 1);
		if (find_key(g_global->env, key) == 0)
			add_to_list(&g_global->env, key, value);
		else
			ft_change_key_value(key, value);
	}
	else if (str[ft_strlen(key)] == '+')
	{
		value = ft_substr(str + ft_strlen(key) + 2, 0, ft_strlen(str)
				- ft_strlen(key) - 2);
		if (find_key(g_global->env, key) == 0)
			add_to_list(&g_global->env, key, value);
		else
		{
			tmp = ft_strjoin(help_expand(key), value);
			ft_lstremove(key);
			add_to_list(&g_global->env, key, tmp);
		}
	}
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
