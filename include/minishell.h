/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:30:09 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/14 16:54:25 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "execution.h"
#include "parting.h"

typedef struct s_global
{
    t_env   *env;
    int     flag;
    int     exit_status;
    int     separator; // 0 if = and 1 if +=
    char *current_path;
    char *old_path;
}           t_global;

extern t_global *g_global;

void    ft_execution(t_minishell *strct);
void	ft_export(t_minishell *strct);
int ft_check_export_unset_args(char *str);
void    ft_check_key(char *str);
char *ft_strcat(char *dest, const char *src);
void    ft_change_curr_and_old_path(char *new_path);

#endif