/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:21:18 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/29 20:47:41 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// Function to free the linked env_list
 void free_list(t_env *head)
 {
     t_env *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        if(tmp->key)
            free(tmp->key);
        // if(tmp->value)
        //     free(tmp->value);
        free(tmp);
    }
}

void    ft_free_global()
{
    if(g_global->env)
        free_list(g_global->env);
    if(g_global->pwd)
        free(g_global->pwd);
    if(g_global->oldpwd)
        free(g_global->oldpwd);
    if(g_global->underscore)
        free(g_global->underscore);
    free_minishell(&g_global->strct);
    // free(g_global);
}