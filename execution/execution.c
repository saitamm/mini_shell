/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/28 18:29:43 by lai-elho         ###   ########.fr       */
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

void ft_bashlvl(t_minishell *strct)
{
    t_env *env = g_global->env;
    if(ft_strcmp(strct->cmd[0], "./minishell") == 0)
    {
        while (env)
        {
            if(ft_strcmp(env->key, "SHLVL") == 0)
            {
                int shlvl = ft_atoi(env->value);
                shlvl++;
                if(shlvl == 1000)  
                    shlvl = 1;
                char *new_value = malloc(12); // Enough space for an int (max 10 digits + sign + null terminator)
                if (!new_value)
                    return;
                printf("new_value %d", shlvl);
                free(env->value);
                env->value = ft_itoa(shlvl);
                return;
            }
            env = env->next;
        }
    }
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
        ft_cd(strct->cmd[1]);
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
    if (access(strct->cmd[0], X_OK) == -1 && strct->cmd[0][0] == '.' && strct->cmd[0][1] == '/')
	{
		perror(strct->cmd[0]);
        g_global->exit_status = 126;
		exit(g_global->exit_status);
	}
    char *path = get_path(help_expand("PATH"), strct->cmd[0]);
        if (!path)
        {
            write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
            write(2, ": command not found\n", 21);
            g_global->exit_status = 127;
            exit(g_global->exit_status);
        }
        dprintf(2, "===> %s\n", strct->cmd[0]);
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

int is_built(char *str)
{
    if (!str || !str || !str)
        return 0;
    if (!ft_strcmp(str, "exit") || !ft_strcmp(str, "export") || !ft_strcmp(str, "cd"))
        return (1);
    if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "unset") || !ft_strcmp(str, "echo"))
        return (1);
    if (!ft_strcmp(str, "env"))
        return 1;
    return (0);
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
void ft_underscore(t_minishell *strct)
{
    char **cmd = strct->cmd;
    int i = 0;
    while(cmd[i])
    {
        g_global->underscore = cmd[i];
        i++;
    }
}



void execute_cmd(t_minishell *strct)
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

void ft_execution()
{
    execute_cmd(g_global->strct);
}