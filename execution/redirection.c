/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:17:14 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/29 10:55:25 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_infile(t_minishell *strct)
{
    int infile_fd;

    if (strct->files->flag == AMB)
    {
        write(2, "Minishell:", 11);
        write(2, strct->files->file, ft_strlen(strct->files->file));
        write(2, ": ambiguous redirect\n", 22);
        g_global->exit_status = 1;
        exit(g_global->exit_status);
    }
    infile_fd = open(strct->files->file, O_RDONLY);
    if (infile_fd == -1)
    {
        if (access(strct->files->file, F_OK) != 0)
        {
            write(2, "Minishell:", 11);
            perror(strct->files->file);
            g_global->exit_status = 1;
            exit(g_global->exit_status);
        }
        else if (access(strct->files->file, R_OK) != 0)
        {
            write(2, "Minishell:", 11);
            perror(strct->files->file);
            g_global->exit_status = 1;
            close(infile_fd);
            exit(g_global->exit_status);
        }
        perror("Error opening file\n");
        g_global->exit_status = 1;
        exit(g_global->exit_status);
    }
    if (ft_strcmp(strct->files->file, "/dev/stdin"))
    {
        if (dup2(infile_fd, STDIN_FILENO) == -1)
        {
            perror("Error in dup2\n");
            g_global->exit_status = 1;
            close(infile_fd);
            exit(g_global->exit_status);
        }
    }
    close(infile_fd);
    return 0;
}

int ft_outfile(t_minishell *strct)
{
    int outfile_fd;

    if (strct->files->flag == AMB)
    {
        write(2, "Minishell:", 11);
        write(2, strct->files->file, ft_strlen(strct->files->file));
        write(2, ": ambiguous redirect\n", 22);
        g_global->exit_status = 1;
        return 1;
    }
    outfile_fd = open(strct->files->file, O_CREAT | O_TRUNC | O_WRONLY, 0640);
    if (outfile_fd == -1)
    {
        write(2, "Minishell:", 11);
        perror(strct->files->file);
        g_global->exit_status = 1;
        close(outfile_fd);
        exit(g_global->exit_status);
    }
    if (ft_strcmp(strct->files->file, "/dev/stdout"))
    {

        if (dup2(outfile_fd, STDOUT_FILENO) == -1)
        {
            write(2, "Error with dup2\n", 17);
            g_global->exit_status = 1;
            close(outfile_fd);
            return 1;
        }
        close(outfile_fd);
        return 0;
    }
    return 0;
}
int ft_append(t_minishell *strct)
{
    int fd;

    if (strct->files->flag == AMB)
    {
        write(2, "Minishell:", 11);
        write(2, strct->files->file, ft_strlen(strct->files->file));
        write(2, ": ambiguous redirect \n", 22);
        g_global->exit_status = 1;
        return 1;
    }
    fd = open(strct->files->file, O_CREAT | O_WRONLY | O_APPEND, 0640);
    if (fd == -1)
    {
        write(2, "Minishell:", 11);
        perror(strct->files->file);
        g_global->exit_status = 1;
        close(fd);
        exit(g_global->exit_status);
    }
    if (ft_strcmp(strct->files->file, "/dev/stdout"))
    {

        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            write(2, "Error with dup2\n", 17);
            g_global->exit_status = 1;
            close(fd);
            return 1;
        }
        close(fd);
        return 0;
    }
    return 0;
}

int redirection(t_minishell *strct)
{
    t_minishell *head = strct;
   
    if (head->files == NULL && head->next && head)
    {
        if (dup2(g_global->fd_pipe[1], STDOUT_FILENO) == -1)
        {
            perror("");
        }
        return (0);
    }
    dup2(g_global->save_fd_out, STDOUT_FILENO);
    int flag;
    flag = 0;
    while (head && head->files)
    {
        if (head->files->file_type == IN || head->files->file_type == HER_DOC)
            ft_infile(head);
        else if (head->files->file_type == 1)
            {
                flag = 1;
                ft_outfile(head);
            }
        else if (head->files->file_type == 3)
        {
            flag = 1;
            ft_append(head);
        }
        head->files = head->files->next;
    }
    if (flag == 0 && strct->next)
        dup2(g_global->fd_pipe[1], STDOUT_FILENO);
        
    return 0;
}