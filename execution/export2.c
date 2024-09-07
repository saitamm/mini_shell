/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:09:53 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/07 21:57:37 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *find_key(t_env *env, const char *key) {
    while (env) {
        if (strcmp(env->key, key) == 0) 
            return env;
        env = env->next;
    }
    return NULL;
}

int process_env_variable(char *str) {
    char *key, *value;
    int append = 0;
    t_env *entry;

    char *op = strstr(str, "+=");
    if (op) {
        append = 1;
        key = strndup(str, op - str);
        value = strdup(op + 2);
    } else if ((op = strchr(str, '='))) {
        key = strndup(str, op - str);
        value = strdup(op + 1);
    } else {
        return 0;
    }

    entry = find_key(g_global->env, key);
    if (entry) {
        if (append) {
            char *new_value = malloc(strlen(entry->value) + strlen(value) + 1);
            strcpy(new_value, entry->value);
            strcat(new_value, value);
            free(entry->value);
            entry->value = new_value;
        } else {
            free(entry->value);
            entry->value = strdup(value);
        }
        free(key);
        free(value);
        return 1;
    } else {
        free(key);
        free(value);
        return 0;
    }
}
