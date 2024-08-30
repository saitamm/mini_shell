/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:49:44 by lai-elho          #+#    #+#             */
/*   Updated: 2024/08/30 11:36:17 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_env(t_env *head)
{
    while (head->next)
    {
        printf("%s = %s\n", head->key, head->value);
        head = head->next;
    }
}
