/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/26 13:03:07 by lai-elho         ###   ########.fr       */
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
        write(2, ": ambiguous redirect", 21);
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
            g_global->exit_status = 127;
            exit(g_global->exit_status);
        }
        else if (access(strct->files->file, R_OK) != 0)
        {
            write(2, "Minishell:", 11);
            perror(strct->files->file);
            g_global->exit_status = 126;
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
        write(2, ": ambiguous redirect", 21);
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
            printf("Error with dup2\n");
            g_global->exit_status = 1;
            close(outfile_fd);
            return 1;
        }
        close(outfile_fd);
        return 0;
    }
    return 0;
}

// void ft_nbr_herdoc(t_minishell *strct)
// {
//     t_minishell *head = strct;
//     t_file *files_head;
//     while (head)
//     {
//         files_head = head->files;
//         while (files_head)
//         {
//             if (files_head->file_type == 2)
//                 g_global->nbr_herdoc++;
//             files_head = files_head->next;
//         }
//         head = head->next;
//     }
// }

// void ft_create_herdoc_pipe()
// {
//     int i = 0;
//     ft_nbr_herdoc(g_global->strct);
//     g_global->pipe_fd = malloc(sizeof(int *) * (g_global->nbr_herdoc + 1));
//     // if(!g_global->pipe_fd)
//     // {
//     //     return 0; //ft free all
//     // }

//     g_global->pipe_fd[g_global->nbr_herdoc] = NULL;
//     while (i < g_global->nbr_herdoc)
//     {
//         g_global->pipe_fd[i] = malloc(sizeof(int) * 2);
//         // if(!g_global->pipe_fd[i])
//         // {
//         //     return 0; //ft free all
//         // }
//         if (pipe(g_global->pipe_fd[i]) != 0)
//         {
//             return; // free
//         }
//         i++;
//     }
// }

// void ft_write_in_pipe(t_file *files_head)
// {
//     int i;

//     i = 0;
//     char *line = readline(">> ");
//     while (line && ft_strcmp(files_head->file, line) != 0)
//     {
//         while ((need_expand_her_doc(line, &i, files_head->flag)))
//             line = expand_str(line, i);
//         write(g_global->pipe_fd[g_global->i_pip_herdoc][1], line, ft_strlen(line));
//         write(g_global->pipe_fd[g_global->i_pip_herdoc][1], "\n", 1);
//         free(line);
//         line = readline(">> ");
//     }
//     if (line)
//         free(line);
//     g_global->i_pip_herdoc++;
// }

// void ft_herdoc()
// {
//     t_minishell *head = g_global->strct;
//     t_file *files_head;
//     ft_create_herdoc_pipe();
//     while (head)
//     {
//         files_head = head->files;
//         while (files_head)
//         {
//             if (files_head->file_type == 2)
//                 ft_write_in_pipe(files_head);
//             files_head = files_head->next;
//         }
//         head = head->next;
//     }
//     g_global->i_pip_herdoc = 0;
// }

// int ft_read_herdoc()
// {
//     if (dup2(g_global->pipe_fd[g_global->i_pip_herdoc++][0], STDIN_FILENO) == -1)
//     {
//         perror("Error in dup2\n");
//         g_global->exit_status = 1;
//         return 1;
//     }
//     return 0;
// }

void ft_close_herdoc_pipe()
{
    int i;

    i = 0;
    while (i < g_global->nbr_herdoc)
    {
        close(g_global->pipe_fd[i][0]);
        close(g_global->pipe_fd[i][1]);
        i++;
    }
}

int ft_append(t_minishell *strct)
{
    int fd;

    if (strct->files->flag == AMB)
    {
        write(2, "Minishell:", 11);
        write(2, strct->files->file, ft_strlen(strct->files->file));
        write(2, ": ambiguous redirect", 21);
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
            printf("Error with dup2\n");
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
        printf("------------->\n");
        if (dup2(g_global->fd_pipe[1], STDOUT_FILENO) == -1)
        {
            printf("in red \n");
            // perror("");
        }
        return (0);
    }
    // if (head && head->next != NULL)
    // {
    //     dup2(g_global->fd_pipe[1], STDOUT_FILENO);
    //     return 0;
    // }

    dup2(g_global->save_fd_out, STDOUT_FILENO);

    while (head && head->files)
    {
        printf("---------------->\n");
        print(g_global->strct);
        if (head->files->file_type == IN || head->files->file_type == HER_DOC)
            ft_infile(head);
        else if (head->files->file_type == 1)
            ft_outfile(head);
        else if (head->files->file_type == 3)
            ft_append(head);
        head->files = head->files->next;
    }
    return 0;
}

void ft_builtins(t_minishell *strct)
{
    if (!strct || !strct->cmd || !strct->cmd[0])
        return;
    else if (ft_strcmp(strct->cmd[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(strct->cmd[0], "env") == 0)
        print_env(g_global->env);
    else if (ft_strcmp(strct->cmd[0], "echo") == 0)
        ft_echo(strct->cmd);
    else if (ft_strcmp(strct->cmd[0], "cd") == 0)
        ft_cd(strct->cmd[1]);
    else if (ft_strcmp(strct->cmd[0], "unset") == 0)
        unset(strct->cmd);
    else if (ft_strcmp(strct->cmd[0], "export") == 0)
        ft_export(strct);
    else if (ft_strcmp(strct->cmd[0], "exit") == 0)
        ft_exit(strct->cmd);
    else
    {
        dprintf(2, "=================> %s \n", strct->cmd[0]);
        
        execve(get_path(help_expand("PATH"), strct->cmd[0]), strct->cmd, env_to_array(g_global->env));
    }
}

void ft_exec_child(t_minishell *strct)
{
    // printf("-------teeeest------>\n");
    redirection(strct);
    ft_builtins(strct);
    //////////////////// we need to add exit to kill the child proccess before reching the execve
    //////////////////// ft_ckeck_cmd(); cmd not founc : perm denied
    // close(g_global->fd_pipe[0]);
    // close(g_global->fd_pipe[1]);
}

void execute_cmd(t_minishell *strct)
{
    while (strct)
    {

        if (pipe(g_global->fd_pipe) == -1)
        {
            perror("pipe error");
            exit(1);
        }
        g_global->pid = fork();
        if (g_global->pid == 0)
        {
            ft_exec_child(strct);
        }
        close(g_global->fd_pipe[1]);
        dup2(g_global->fd_pipe[0], STDIN_FILENO);
        //   close(g_global->fd_pipe[0]);
        strct = strct->next;
    }
    while (wait(NULL) != -1)
        ;
}

// void execute_cmd(t_minishell *strct)
// {
//     while (strct)
//     {
//         if (pipe(g_global->fd_pipe) == -1)
//         {
//             perror("pipe error");
//             exit(1);
//         }

//         g_global->pid = fork();
//         if (g_global->pid == 0)  // Child process
//         {
//             if (strct->next != NULL) // If there is a next command
//             {
//                 if (dup2(g_global->fd_pipe[1], STDOUT_FILENO) == -1) // Redirect stdout to pipe
//                 {
//                     perror("dup2 error");
//                     exit(1);
//                 }
//             }

//             close(g_global->fd_pipe[0]); // Close read end in the child process
//             close(g_global->fd_pipe[1]); // Close write end after duplication
//             ft_exec_child(strct); // Execute the command
//         }

//         // Parent process: only handles input redirection for the next command
//         close(g_global->fd_pipe[1]);  // Close write end in the parent process
//         if (dup2(g_global->fd_pipe[0], STDIN_FILENO) == -1)  // Redirect stdin for the next command
//         {
//             perror("dup2 error");
//             exit(1);
//         }
//         close(g_global->fd_pipe[0]);  // Close read end after duplication

//         strct = strct->next;  // Move to the next command in the pipe chain
//     }

//     while (wait(NULL) != -1);  // Wait for all child processes to finish
// }

void ft_execution()
{
    execute_cmd(g_global->strct);
}