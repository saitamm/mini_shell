/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:30:09 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/17 15:30:32 by lai-elho         ###   ########.fr       */
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
    int nbr_herdoc;
    int **pipe_fd;
    int i_pip_herdoc;
    int save_fd_out;
    int save_fd_int;
    int pid;
    int fd_pipe[2];
    t_minishell *strct;
}           t_global;

extern t_global *g_global;

void    ft_execution();
void	ft_export(t_minishell *strct);
int ft_check_export_unset_args(char *str);
void    ft_check_key(char *str);
char *ft_strcat(char *dest, const char *src);
void    ft_change_curr_and_old_path(char *new_path);
int	ft_lstsize2(t_minishell *lst);

void ft_write_in_pipe(t_file *files_head);


#endif