/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:13:05 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/17 16:40:42 by sait-amm         ###   ########.fr       */
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

void	print_export()
{
	t_env	*tmp;

	tmp = g_global->env;
	int i = 0;
	ft_list_sort(&tmp);
	while (tmp)
	{
		if (tmp->value && tmp->key)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (!tmp->value)
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
		i++;
	}
}

void	ft_export(t_minishell *strct)
{
	int	i;

	i = 1;
	if (!strct->cmd[i] || (strct->cmd[i][0] == '\0' && strct->cmd[i + 1] == NULL)) {
		print_export();
	} else {
		while (strct->cmd[i]) {
			ft_check_key(strct->cmd[i]);
			i++;
	 	}
	}
}


// int		check_error_export(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[0] == '-')
// 		{
// 			write(1, "not a valid option\n", 24);
// 			return (1);
// 		}
// 	if (!ft_isalpha(str[i]) && str[0] != '_')
// 		{
			
// 			write(1, "not a valid identifier\n", 24);
// 			return (1);
// 		}
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (str[i] == '+' && str[i + 1] == '=')
// 			break;
// 		if (!ft_isalnum(str[i]) && str[i] != '_')
// 		{
// 			write(2, "not a valid identifier\n", 24);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
// void	ft_export(t_minishell *strct)
// {
// 	int		i;

// 	i = 1;
// 	if (strct->cmd[1] == NULL)
// 		print_export();
// 	else
// 	{
// 		while (strct->cmd[i])
// 		{
// 			if (!check_error_export(strct->cmd[1]))
// 				break;
// 			i++;
// 		}
// 	}
// }
