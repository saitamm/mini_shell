/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:52:20 by lai-elho          #+#    #+#             */
/*   Updated: 2024/08/28 13:43:20 by sait-amm         ###   ########.fr       */
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

// Function to add a new node to the linked list

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
    while(env_var[i] != '=' && env_var)
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
        key [i] = env_var[i];
        i++;
    }
    return (key);
}

// Function to parse the environment variable string and add it to the linked list

void parse_env_var(t_env **head, char **env_var)
{
    char *key = NULL;
    char *value = NULL;

    int i = 0;
    while(env_var[i])
    {
        // printf("foooooor debug\n");
        char *equal_sign = strchr(env_var[i], '=');
        if (equal_sign)
        {
            key = ft_putkey(env_var[i]);
            value = strdup(equal_sign + 1);
            // printf("********************%s\n", key);
            add_to_list(head, key, value);

            free(key);
            free(value);
        }
        i++;
    }
}

//Function to free the linked list

void free_list(t_env *head)
{
    t_env *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}