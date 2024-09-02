/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:54:41 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/02 10:24:21 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_find_in_env(char *search_key) {
    while (g_global->env != NULL) {
        if (strcmp(g_global->env->key, search_key) == 0) {
            printf("%s\n", g_global->env->value);
            return;
        }
        g_global->env = g_global->env->next;
    }
    printf("Key not found: %s\n", search_key);
}

void ft_echo(char **str) {
    int j = 1;
    int i = 0;
    int flag = 1;

    if (str[1] && str[1][0] == '-' && str[1][1] == 'n' && str[1][2] == '\0') {
        flag = 0;
        j++;
    }
    while (str[j]) {
        i = 0;
        if (str[j][0] == '"') {
            if (str[j][1] == '$') {
                ft_find_in_env(str[j]);
            }
            else {
                while (str[j][i]) {
                    write(1, &str[j][i], 1);
                    i++;
                }
            }
        }
        else if (str[j][0] == '\'' || str[j][0] != '\0') {
            while (str[j][i]) {
                write(1, &str[j][i], 1);
                i++;
            }
        }
        if (str[j + 1]) {
            write(1, " ", 1);
        }
        j++;
    }
    if (flag == 1) {
        write(1, "\n", 1);
    }
}
