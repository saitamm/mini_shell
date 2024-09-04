/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:52:20 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/04 15:31:10 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env *create_node(char *key, char *value)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return NULL;

    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;

    return new_node;
}

void add_to_list(t_env **head, char *key, char *value)
{
    t_env *new_node = create_node(key, value);
    if (!new_node)
        return;
    new_node->next = *head;
    *head = new_node;
}

int ft_find_key_len(char *env_var)
{
    int i = 0;
    while (env_var[i] != '=' && env_var)
        i++;
    return (i);
}

char *ft_putkey(char *env_var)
{
    int i = 0;
    int key_len = ft_find_key_len(env_var);
    char *key = malloc(key_len);

    while (i < key_len)
    {
        key[i] = env_var[i];
        i++;
    }
    return (key);
}

char *get_key(char *s)
{
    int i = 0;

    while (s[i] && s[i] != '=')
        i++;
    char *new = malloc((sizeof(char) * i) + 1);
    if (!new)
        return (NULL);
    int j = 0;
    while (j < i)
    {
        new[j] = s[j];
        j++;
    }
    new[j] = '\0';
    return (new);
}

void parse_env_var(char **env_var)
{
    int i = 0;

    if (env_var == NULL)
        return;
    while (env_var[i])
    {
        char *equal_sign = ft_strchr(env_var[i], '=');
        if (equal_sign)
        {
            char *key = get_key(env_var[i]);
            char *value = equal_sign + 1;

            if (!key || !value)
            {
                // free(key);
                // free(value);
                return;
            }
            add_to_list(&g_global->env, key, value);
            free(key);
            // free(value);
        }
        i++;
    }
}

// Function to free the linked list
//  void free_list(t_env *head)
//  {
//      t_env *tmp;

//     while (head)
//     {
//         tmp = head;
//         head = head->next;
//         free(tmp->key);
//         free(tmp->value);
//         free(tmp);
//     }
// }