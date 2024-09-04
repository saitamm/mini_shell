/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:49:44 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/04 14:15:18 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_env(t_env *head)
{
    t_env *temp = head;
   
        while (temp)
        {
            if (temp->key && temp->value)
                printf("%s = %s\n", temp->key, temp->value);
            temp = temp->next;
        }
}
