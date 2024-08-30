/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:54:41 by lai-elho          #+#    #+#             */
/*   Updated: 2024/08/29 15:44:07 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_find_in_env(char *to_find, char **env)
{
    int i = 0;
    int len = ft_strlen(to_find);
    int path_len;

    while (env[i])
    {
        if (ft_strncmp(env[i], to_find, len) == 0 && env[i][len] == '=')
        {
            path_len = ft_strlen (&env[i][len + 1]);
            write(1, &env[i][len + 1], path_len);
            write(1, "\n", 1);
            return;
        }
        i++;
    }
    write(1, "Variable not found\n", 19);
}

void    ft_echo(int ac, char **str, char **env)
{
    int j = 1;
    int i;
    int flag = 1;

    if(str[1][0] == '-' && str[1][1] == 'n')
    {
        flag = 0;
        j++;
    }
    
    while(j < ac)
    {
        i = 0;
        if(str[j][0] == '\'')
        {
            while(str[j][i])
            {
                write(1,&str[j][i],1);
                i++;
            }
        }
        else if(str[j][0] == '"' && str[j][1] != '$')
        {
            while(str[j][i])
            {
                write(1,&str[j][i],1);
                i++;
            }
        }
        else if(str[j][0] == '"' && str[j][1] == '$')
        {
            ft_find_in_env(str[j] , env);
        }
        else 
        {
            while(str[j][i])
            {
                write(1,&str[j][i],1);
                i++;
            }
        }
        if(j < ac - 1)
            write(1," ",1);
        j++;
    }
    if(flag == 1)
        write(1,"\n",1);
}