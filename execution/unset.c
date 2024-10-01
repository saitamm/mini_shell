/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:11:54 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/01 21:35:01 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstremove(char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!g_global || !g_global->env || !key)
		return ;
	current = g_global->env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				g_global->env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset(char **cmd)
{
	int i;
	i = 1;

	while (cmd[i])
	{
		if (ft_check_export_unset_args(cmd[i]) == 0)
			return 0;
		ft_lstremove(cmd[i]);
		if (!ft_strcmp(cmd[i], "PWD"))
			g_global->pwd = ft_strdup(NULL);
		i++;
	}
	return (0);
}