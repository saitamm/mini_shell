/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/21 21:17:44 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int ft_infile(t_minishell *strct)
{
    int infile_fd;

    if (strct->files->flag == 1)
    {
        printf("ambiguous redirect\n");
        g_global->exit_status = 1;
        return 1;
    }
    if (access(strct->files->file, F_OK) != 0)
    {
        printf("file does not exist\n");
        g_global->exit_status = 127;
        return 1;
    }
    else if (access(strct->files->file, R_OK) != 0)
    {
        printf("Permission denied\n");
        g_global->exit_status = 126;
        return 1;
    }
    infile_fd = open(strct->files->file, O_RDONLY);
    if (infile_fd == -1)
    {
        perror("Error opening file\n");
        g_global->exit_status = 1;
        return 1;
    }
    if (dup2(infile_fd, STDIN_FILENO) == -1)
    {
        perror("Error in dup2\n");
        g_global->exit_status = 1;
        close(infile_fd);
        return 1;
    }
    // printf("success in opening and duping\n");
    close(infile_fd);
    return 0;
}

int ft_outfile(t_minishell *strct)
{
    int outfile_fd;

    if (strct->files->flag == 1)
    {
        printf("ambiguous redirect\n");
        g_global->exit_status = 1;
        return 1;
    }
    outfile_fd = open(strct->files->file, O_CREAT | O_TRUNC | O_WRONLY, 0640);
    if (outfile_fd == -1)
    {
        printf("permition denied\n");
        g_global->exit_status = 126;
        return 1;
    }

    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
    {
        printf("Error with dup2\n");
        g_global->exit_status = 1;
        close(outfile_fd);
        return 1;
    }
    close(outfile_fd);
    return 0;
}

int ft_append(t_minishell *strct)
{
    int outfile_fd;

    if (strct->files->flag == 1)
    {
        printf("ambiguous redirect\n");
        g_global->exit_status = 1;
        return 1;
    }
    outfile_fd = open(strct->files->file, O_CREAT | O_WRONLY | O_APPEND, 0640);
    if (outfile_fd == -1)
    {
        printf("permition denied");
        g_global->exit_status = 126;
        return 1;
    }

    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
    {
        printf("Error with dup2");
        g_global->exit_status = 1;
        close(outfile_fd);
        return 1;
    }
    // printf("success in opening and duping\n");
    close(outfile_fd);
    return 0;
}

int redirection(t_minishell *strct)
{
    t_file *head = strct->files;

    while (strct->files)
    {
        // printf("honaaaaaaaaaaaaaaaaaa %s\n\n", strct->files->file);
        if (strct->files->file_type == 0)
        {
            if (ft_infile(strct) == 1)
                return 1;
        }
        if (strct->files->file_type == 1)
        {
            if (ft_outfile(strct) == 1)
                return 1;
        }
        if (strct->files->file_type == 3)
        {
            if (ft_append(strct) == 1)
                return 1;
        }
        strct->files = strct->files->next;
    }
    strct->files = head;
    return 0;
}

void ft_builtins(t_minishell *strct)
{
    if (!strct || !strct->cmd || !strct->cmd[0])
        return;
    printf("\n\n==================================================================> \n\n");
    if (ft_strcmp(strct->cmd[0], "pwd") == 0)
        ft_pwd();
    if (ft_strcmp(strct->cmd[0], "env") == 0)
        print_env(g_global->env);
    if (ft_strcmp(strct->cmd[0], "echo") == 0)
        ft_echo(strct->cmd);
    if (ft_strcmp(strct->cmd[0], "cd") == 0)
        ft_cd(strct->cmd[1]);
    if (ft_strcmp(strct->cmd[0], "unset") == 0)
        unset(strct->cmd);
    if (ft_strcmp(strct->cmd[0], "export") == 0)
        ft_export(strct);
    if (ft_strcmp(strct->cmd[0], "exit") == 0)
        ft_exit(strct->cmd);
}
void execute_cmd(t_minishell *strct)
{
    int out;
    int in;

    out = dup(1); // protect
    in = dup(0);  // protect
    // cpy(out,in);
    if (redirection(strct) == 1)
    {
        // printf("erooor \n\n");
        return;
    }
    ft_builtins(strct);
    dup2(out, 1); // protect
    dup2(in, 0);  // protect
    // ft_to_place(out,in);
}

void ft_execution(t_minishell *strct)
{
    // ft_herdoc();
    execute_cmd(strct);
}