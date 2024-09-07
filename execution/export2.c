/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:09:53 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/07 01:10:56 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// // Function to safely duplicate strings
// char *ft_strdup(const char *src) {
//     char *dup = malloc(strlen(src) + 1);
//     if (!dup)
//         return NULL;
//     strcpy(dup, src);
//     return dup;
// }

// // Function to find key length (before '=' or '+=')
// int find_key_len(const char *str) {
//     int i = 0;
//     while (str[i] && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
//         i++;
//     return i;
// }

// // Function to extract the key (before '=' or '+=')
// char *extract_key(const char *str) {
//     int key_len = find_key_len(str);
//     char *key = malloc(key_len + 1);
//     if (!key)
//         return NULL;

//     strncpy(key, str, key_len);
//     key[key_len] = '\0';  // Null-terminate the key
//     return key;
// }

// // Search for the key in the linked list
// t_env *search_key(t_env *head, const char *key) {
//     while (head) {
//         if (strcmp(head->key, key) == 0)
//             return head;
//         head = head->next;
//     }
//     return NULL;  // Key not found
// }

// // Function to update or append to the value
// void modify_value(t_env *node, const char *str) {
//     char *equal_sign = strchr(str, '=');
    
//     if (!equal_sign)
//         return;  // No '=' found, invalid input
    
//     // Check if it's an append operation "+="
//     if (*(equal_sign - 1) == '+') {
//         char *new_value = ft_strdup(equal_sign + 1);
//         if (!new_value)
//             return;

//         // Append new_value to the existing value
//         char *combined_value = malloc(strlen(node->value) + strlen(new_value) + 1);
//         if (!combined_value) {
//             free(new_value);
//             return;
//         }
//         strcpy(combined_value, node->value);
//         strcat(combined_value, new_value);

//         free(node->value);  // Free the old value
//         node->value = combined_value;  // Update with the combined value
//         free(new_value);  // Free the new_value
//     } else {
//         // Update with the new value after '='
//         free(node->value);  // Free the old value
//         node->value = ft_strdup(equal_sign + 1);
//     }
// }

// // Function to process the input string and modify the linked list
// void process_str(t_env **env_list, const char *str) {
//     char *key = extract_key(str);
//     if (!key)
//         return;  // Memory allocation failed

//     // Search for the key in the linked list
//     t_env *node = search_key(*env_list, key);

//     if (node) {
//         // Key found, modify its value
//         modify_value(node, str);
//     } else {
//         // Key not found, create a new node and add it to the list
//         char *equal_sign = strchr(str, '=');
//         if (equal_sign) {
//             char *value = ft_strdup(equal_sign + 1);
//             t_env *new_node = malloc(sizeof(t_env));
//             if (new_node) {
//                 new_node->key = ft_strdup(key);
//                 new_node->value = value;
//                 new_node->next = *env_list;
//                 *env_list = new_node;
//             }
//         }
//     }

//     free(key);  // Free the extracted key
// }
