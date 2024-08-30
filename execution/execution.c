/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/08/30 13:27:40 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_execution(t_minishell *strct, t_execution *exec)
{
    if(strcmp(strct->cmd[0], "pwd") == 0)
        ft_pwd();
    if(strcmp(strct->cmd[0], "cd") == 0)
        ft_cd(strct->cmd[1]);
    if(strcmp(strct->cmd[0], "env") == 0)
        print_env(g_global->env);
    if(strcmp(strct->cmd[0], "echo") == 0)
        ft_echo(exec->ac, exec->av, exec->env);
    if(strcmp(strct->cmd[0], "unset") == 0)
        unset(exec->av);
}