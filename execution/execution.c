/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/18 13:34:33 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_execution(t_minishell *strct)
{
    if (!strct->cmd[0])
        return;
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