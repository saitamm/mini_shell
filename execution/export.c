/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:13:05 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/06 22:52:07 by lai-elho         ###   ########.fr       */
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

void ft_add_to_export(char *str) {
    char *equal_sign = strchr(str, '=');

    if (equal_sign) {
        char *key = get_key(str);  // Get the key up to the '='
        char *value = equal_sign + 1;  // Get value after '='

        if (key && value) {
            add_to_list(&g_global->env, key, value);
        }
        
        free(key);  // Free the key memory after it's used
    } else {
        // If there is no '=', treat the whole string as a key with an empty value
        char *key = ft_strdup(str);
        if (key) {
            add_to_list(&g_global->env, key, "");  // Add with an empty value
        }
        free(key);
    }
}

void	ft_export(t_minishell *strct)
{
	int	i;

	i = 1;
	// If no arguments passed, or if the first argument is empty, print current export
	if (!strct->cmd[i] || (strct->cmd[i][0] == '\0' && strct->cmd[i + 1] == NULL)) {
		print_export();  // Function to print environment variables
	} else {
		// Process each command argument and add it to the export list
		while (strct->cmd[i]) {
			ft_add_to_export(strct->cmd[i]);
			i++;
	 	}
	}
}     