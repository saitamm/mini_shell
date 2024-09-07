/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:09:53 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/07 12:02:22 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char *ft_return_key(char *cmd, int key_len)
// {
//     char *key;
//     int i = 0;

//     key = malloc((key_len + 1) * sizeof(char));
//     while (i < key_len)
//     {
//         key[i] = cmd[i];
//         i++;
//     }
//     return key;
// }

// char    *ft_find_key(char *cmd)
// {
//     int key_len = ft_find_key_len(cmd);
//     char *str = ft_return_key(cmd, key_len);
//     return  str;
// }
// void    ft_concat_value()
// {
//     printf(" \nft_concat_value(key)\n");
// }

// void    ft_change_value()
// {
//     printf("\nft_chnge value\n");
// }

// int ft_exist_key(char *key)
// {   
//     t_env *head = g_global->env;
//     while(g_global->env)
//     {
//         if(g_global->env->key == key && g_global->flag == 1)
//         {
//             ft_concat_value();
//             return 0;
//         }
//         else if(g_global->env->key == key)
//         {
//             ft_change_value();
//             return 0;
//         }
//         g_global->env = g_global->env->next;
//     }
//     g_global->env = head;
//     return 1;
// }

// int ft_check_modify_export(char *cmd)
// {
//     char *key;
//     key = ft_find_key(cmd);
//     if(!key)
//         return (0);
//     int i = ft_exist_key(key);
//     return i;
// }

