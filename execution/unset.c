/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:11:54 by lai-elho          #+#    #+#             */
/*   Updated: 2024/08/29 17:11:25 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdlib.h>
#include <string.h>

void    ft_lstremove( char *key)
{
    t_env   *current;
    t_env   *prev;
    t_env   *temp;

    if (!g_global->env || !key)
        return;

    current = g_global->env;
    prev = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                g_global->env = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void	unset(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		ft_lstremove(av[i]);
		i++;
	}
}