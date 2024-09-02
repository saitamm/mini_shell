/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/02 10:37:33 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_execution(t_minishell *strct, t_execution *exec)
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
        unset(exec->av);
    if(ft_strcmp(strct->cmd[0], "export") == 0)
        ft_export(exec);
}