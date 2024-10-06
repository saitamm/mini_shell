/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:31:58 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 13:15:58 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*create_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (key == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	add_to_list(t_env **head, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_node(key, value);
	if (!new_node)
		return ;
	new_node->next = *head;
	*head = new_node;
}

int	ft_find_key_len(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=' && env_var)
		i++;
	if (env_var[i - 1] == '+')
	{
		g_global->flag = 1;
		i--;
	}
	return (i);
}

char	*ft_putkey(char *env_var)
{
	int		i;
	int		key_len;
	char	*key;

	i = 0;
	key_len = ft_find_key_len(env_var);
	key = malloc(key_len);
	while (i < key_len)
	{
		key[i] = env_var[i];
		i++;
	}
	return (key);
}

void	env_manuel(void)
{
	char	cwd[1024];
	char	*str;
	char	*str2;

	add_to_list(&g_global->env, "PWD", getcwd(cwd, sizeof(cwd)));
	add_to_list(&g_global->env, "SHLVL", "1");
	add_to_list(&g_global->env, "_", "/usr/bin/env");
	str = ft_strjoin("/nfs/homes/sait-amm/bin:/usr/local/sbin",
			":/usr/local/bin:/usr/sbin:");
	str2 = ft_strjoin(str,
			"/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	add_to_list(&g_global->env, "PATH", str2);
	free(str);
	free(str2);
	g_global->flag_env = 0;
}
