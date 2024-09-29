/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/29 10:06:46 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


    int is_directory(const char *path) {
    struct stat path_stat;

    if (access(path , F_OK) != 0) {
        perror("access");
        return 0;  // Path doesn't exist or is inaccessible
    }

    if (stat(path, &path_stat) != 0) {
        perror("stat");
        return 0;
    }

    if (S_ISDIR(path_stat.st_mode)) {
        return 1;  // It's a directory
    }

    return 0; 
}
void execute_child(t_minishell *strct)
{
    if (!strct || !strct->cmd || !strct->cmd[0])
    {
        return;
    }
    else if (ft_strcmp(strct->cmd[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(strct->cmd[0], "env") == 0)
        print_env(g_global->env);
    else if (ft_strcmp(strct->cmd[0], "echo") == 0)
        ft_echo(strct->cmd);
    else if (ft_strcmp(strct->cmd[0], "cd") == 0)
        ft_cd(strct->cmd);
    else if (ft_strcmp(strct->cmd[0], "unset") == 0)
        unset(strct->cmd);
    else if (ft_strcmp(strct->cmd[0], "export") == 0)
        ft_export(strct);
    else if (ft_strcmp(strct->cmd[0], "exit") == 0)
        ft_exit(strct->cmd);
    else
    {

        if (!ft_split(strct->cmd[0], ' ')[0] || strct->cmd[0][0] == '\0')
        {
            write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
            write(2, ": command not found\n", 21);
            g_global->exit_status = 127;
            exit(g_global->exit_status);
        }
        if (ft_strchr(strct->cmd[0], '/'))
        {
            if (access(strct->cmd[0], X_OK) == -1)
            {
            perror(strct->cmd[0]);
            g_global->exit_status = 126;
            exit(g_global->exit_status);
            }
            if (is_directory(strct->cmd[0]))
            {
                write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
                write(2, ": is a directory\n", 18);
            g_global->exit_status = 126;
            exit(g_global->exit_status);
            }
        }
        char *path = get_path(help_expand("PATH"), strct->cmd[0]);
        if (!path)
        {
            write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
            write(2, ": command not found\n", 21);
            g_global->exit_status = 127;
            exit(g_global->exit_status);
        }
        ft_bashlvl(strct);
        char **env_exc = env_to_array(g_global->env);
        execve(path, strct->cmd, env_exc);
    }
    exit(0);
}

void ft_exec_child(t_minishell *strct)
{
    redirection(strct);
    execute_child(strct);
    close(g_global->fd_pipe[0]);
    close(g_global->fd_pipe[1]);
}


int ft_lstsize_minishell(t_minishell *lst)
{
    int i;

    i = 0;
    if (!lst)
        return (0);
    while (lst != NULL)
    {
        i++;
        lst = lst->next;
    }
    return (i);
}


void ft_execution(t_minishell *strct)
{
    int status;
    int st;
    int size = ft_lstsize_minishell(strct);
    int *pid;
    int i = 0;

    pid = malloc(size * sizeof(int));
    if (size == 1 && is_built(strct->cmd[0]))
    {
        redirection(strct);

        ft_builtins(strct);
        ft_underscore(strct);
        dup2(g_global->save_fd_out, STDOUT_FILENO);
        dup2(g_global->save_fd_int, STDIN_FILENO);
    }
    else
    {
        while (strct)
        {

            if (pipe(g_global->fd_pipe) == -1)
            {
                perror("pipe error");
                exit(1);
            }

            else
            {
                pid[i] = fork();
                if (pid[i] == 0)
                    ft_exec_child(strct);
            }
            close(g_global->fd_pipe[1]);
            dup2(g_global->fd_pipe[0], STDIN_FILENO);
            close(g_global->fd_pipe[0]);
            g_global->underscore = ft_strdup(strct->cmd[0]);
            ft_underscore(strct);
            strct = strct->next;
            i++;
        }
        i = 0;
        while (i < size)
        {
            waitpid(pid[i], &status, 0);
            st = status >> 8;
            g_global->exit_status = st;
            i++;
        }
    }
}