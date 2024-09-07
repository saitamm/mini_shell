/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/06 23:17:02 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_execution(t_minishell *strct)
{
    if(ft_strcmp(strct->cmd[0], "pwd") == 0)
        ft_pwd();
    if(ft_strcmp(strct->cmd[0], "env") == 0)
        print_env(g_global->env);
    if(ft_strcmp(strct->cmd[0], "echo") == 0)
        ft_echo(strct->cmd);
    if(ft_strcmp(strct->cmd[0], "cd") == 0)
        ft_cd(strct->cmd[1]);
    if(ft_strcmp(strct->cmd[0], "unset") == 0)
        unset(strct->cmd);
    if(ft_strcmp(strct->cmd[0], "export") == 0)
        ft_export(strct);
    if(ft_strcmp(strct->cmd[0], "exit") == 0)
        ft_exit(strct->cmd);
}