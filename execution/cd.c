/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:11:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/23 10:50:35 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 
#include "../include/minishell.h"

char    *find_home_path()
{
    t_env *head = g_global->env;  
    char * HOME_path = NULL;     

    while(g_global->env)
    {
        if(ft_strcmp(g_global->env->key, "HOME") == 0 )
        {
            // printf("home foundn\n\n\n");
            HOME_path = g_global->env->value;
            return (g_global->env->value);
        }
        else
            g_global->env = g_global->env->next;
    }
    g_global->env = head;
    if(g_global->env->next)
        printf("minishell: cd: HOME not set\n");
    return NULL;
}

// char      *ft_find_current_pwd(void)
// {
//     t_env *head = g_global->env;
//     while(g_global->env)
//     {
//         if(ft_strcmp (g_global->env->key, "PWD") == 0)
//         {
//             g_global->current_path = g_global->env->value;
//             return(g_global->env->value);   
//         }
//         else 
//             g_global->env = g_global->env->next;
//     }
//     g_global->env = head;
//     return NULL;
// }
// void    ft_change_curr_and_old_path(char *new_path)
// {
//     t_env *head = g_global->env;
//     ft_find_current_pwd();
//     while(g_global->env->next)
//     {
//         if(ft_strcmp(g_global->env->key, "OLDPWD") == 0 )
//         {
//             g_global->env->key = g_global->current_path;
//             break;
//         }
//         else
//             g_global->env = g_global->env->next;
//     }
//     g_global->env = head;
    
//       while(g_global->env->next)
//     {
//         if(ft_strcmp(g_global->env->key, "PWD") == 0 )
//         {
//             g_global->env->key = new_path;
//             break;
//         }
//         else
//             g_global->env = g_global->env->next;
//     }
//     g_global->env = head;
// }

void    ft_find_current_pwd(void)
{
    t_env *head = g_global->env;
    
    while (g_global->env)
    {
        if (ft_strcmp(g_global->env->key, "PWD") == 0)
        {
            g_global->current_path = g_global->env->value;
            break;
        }
        else
            g_global->env = g_global->env->next;
    }
    g_global->env = head;
}

void ft_change_curr_and_old_path(char *new_path)
{
    t_env *head = g_global->env;
    while (g_global->env)
    {
        if (ft_strcmp(g_global->env->key, "OLDPWD") == 0)
        {
            free(g_global->env->value);
            g_global->env->value = ft_strdup(g_global->current_path);
            break;
        }
        else
            g_global->env = g_global->env->next;
    }
    
    while (g_global->env)
    {
        if (ft_strcmp(g_global->env->key, "PWD") == 0)
        {
            free(g_global->env->value);
            g_global->env->value = ft_strdup(new_path);  
            break;
        }
        else
            g_global->env = g_global->env->next;
    }
            // printf("teeeest %s\n",new_path);
    g_global->env = head;
}

// problem in cd bohadha the pwd makaitbdlech
void ft_cd(char *Path)
{
    char cwd[1024];

    if (!Path || ft_strcmp(Path, "~") == 0 || ft_strcmp(Path, "--") == 0)
    {
        Path = find_home_path();
        return;
        // ft_find_current_pwd();
        // ft_change_curr_and_old_path(Path);
    }
    
   if (chdir(Path) == 0)
    {
        getcwd(cwd, sizeof(cwd));
        ft_find_current_pwd();
        ft_change_curr_and_old_path(cwd);
        // printf("teeeeest %s\n",cwd);
    }
    else 
    {
        perror(Path);
        g_global->exit_status = 1;
    }
}
