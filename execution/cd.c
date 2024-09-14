/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:11:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/14 10:00:08 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *find_home_path()
{
    t_env *head = g_global->env;  
    char * HOME_path;     

    while(g_global->env->next)
    {
        if(ft_strcmp(g_global->env->key, "HOME") == 0 )
        {
            HOME_path = g_global->env->value;
            return (g_global->env->value);
        }
        else
            g_global->env = g_global->env->next;
    }
    g_global->env = head;
    return NULL;
}

void ft_cd(char *Path)
{
    char cwd[1024];

    if (Path == NULL || ft_strcmp(Path, "~") == 0 || ft_strcmp(Path, "--") == 0)
    {
        Path = find_home_path();
    }
    // if(i == -1)
    //     perror("error");
    if (chdir(Path) == 0)
    {
        getcwd(cwd, sizeof(cwd));
        ft_pwd();
    }
    else 
    {
        perror(Path);
        g_global->exit_status = 1;
    }
        // printf("the path is :%s\n", Path);
}
