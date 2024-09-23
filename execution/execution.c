/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/19 18:37:41 by lai-elho         ###   ########.fr       */
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

void ft_nbr_herdoc(t_minishell *strct)
{
    t_minishell *head = strct;
    t_file *files_head;
    while (head)
    {
        files_head = head->files;
        while (files_head)
        {
            if (files_head->file_type == 2)
                g_global->nbr_herdoc++;
            files_head = files_head->next;
        }
        head = head->next;
    }
}

void ft_create_herdoc_pipe()
{
    int i = 0;
    ft_nbr_herdoc(g_global->strct);
    g_global->pipe_fd = malloc(sizeof(int *) * (g_global->nbr_herdoc + 1));
    // if(!g_global->pipe_fd)
    // {
    //     return 0; //ft free all
    // }

    g_global->pipe_fd[g_global->nbr_herdoc] = NULL;
    while (i < g_global->nbr_herdoc)
    {
        g_global->pipe_fd[i] = malloc(sizeof(int) * 2);
        // if(!g_global->pipe_fd[i])
        // {
        //     return 0; //ft free all
        // }
        if (pipe(g_global->pipe_fd[i]) != 0)
        {
            return; // free
        }
        i++;
    }
}

void ft_write_in_pipe(t_file *files_head)
{
    // write(1, ">> ", 3);
    char *line = readline(">> ");
    while (line && ft_strcmp(files_head->file, line) != 0)
    {
        write(g_global->pipe_fd[g_global->i_pip_herdoc][1], line, ft_strlen(line));
        write(g_global->pipe_fd[g_global->i_pip_herdoc][1], "\n", 1);
        free(line);
        // write(1, ">> ",3);
        line = readline(">> ");
    }
    if (line)
        free(line);
    g_global->i_pip_herdoc++;
}

void ft_herdoc()
{
    t_minishell *head = g_global->strct;
    t_file *files_head;
    ft_create_herdoc_pipe();
    while (head)
    {
        files_head = head->files;
        while (files_head)
        {
            if (files_head->file_type == 2)
                ft_write_in_pipe(files_head);
            files_head = files_head->next;
        }
        head = head->next;
    }
    g_global->i_pip_herdoc = 0;
}

int ft_read_herdoc()
{  
    printf("############# {i_pip : %d} ##############\n", g_global->i_pip_herdoc);
    if (dup2( g_global->pipe_fd[g_global->i_pip_herdoc++][0] , STDIN_FILENO) == -1)
    {
        perror("Error in dup2\n");
        g_global->exit_status = 1;
        return 1;
    }
    return 0;
}

void    ft_close_herdoc_pipe()
{
    int i; 

    i = 0;
    while (i < g_global->nbr_herdoc)
    {
        close (g_global->pipe_fd[i][0]);
        close (g_global->pipe_fd[i][1]);
        i++;
    }
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
    close(outfile_fd);
    return 0;
}

int redirection(t_minishell *strct)
{
    t_file *head = strct->files;
    if (strct && strct->next != NULL)
    {
        dup2(g_global->fd_pipe[1], STDOUT_FILENO);
    }
    else
    {
        // write(2, "+++++++++++++++++++++++\n", 24);
        dup2(g_global->save_fd_out, STDOUT_FILENO);
    }
    while (strct && strct->files)
    {
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
        if (strct->files->file_type == 2)
        {
            if (ft_read_herdoc(strct) == 1)
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


void ft_exec_child(t_minishell *strct)
{
    redirection(strct);//we need to setuo herdoc redirection
    // if (strct->files->flag == 1)
    // {
    //     printf("ambiguous redirect\n");
    //     g_global->exit_status = 1;
    //     return ;
    // }
    // ft_builtins(strct);//we need to add exit to kill the child proccess before reching the execve
    // ft_ckeck_cmd(); cmd not founc : perm denied
    //creat a dublle table from the env struct to pass it to the execve 
    close(g_global->fd_pipe[0]);
    close(g_global->fd_pipe[1]);
    execve(strct->cmd[0], strct->cmd,NULL);

}

void execute_cmd(t_minishell *strct)
{
    
    pipe(g_global->fd_pipe);
    while (strct)
    {
        g_global->pid = fork();
        if (g_global->pid == 0)
        {
            ft_exec_child(strct);
        }
        close(g_global->fd_pipe[1]);
        dup2(g_global->fd_pipe[0], STDIN_FILENO);
        close(g_global->fd_pipe[0]);
        strct = strct->next;
    }
    while (wait(NULL) != -1);
}

void ft_execution()
{
    ft_herdoc();
    execute_cmd(g_global->strct);
}