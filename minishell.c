/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:29:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/04 16:41:41 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_global *g_global = NULL;

void print(t_minishell *strct)
{
    t_file *tmp2;
    while (strct != NULL)
    {
        int i = 0;
        tmp2 = strct->files;
        while (strct->cmd[i])
        {
            printf("command %d >>>> *%s*\n", i, strct->cmd[i]);
            i++;
        }
        while (tmp2)
        {
            printf("file  >>>>*%s*\n", tmp2->file);
            printf("file type = %d\n", tmp2->file_type);
            printf("flag  = %d\n", tmp2->flag);
            tmp2 = tmp2->next;
        }
        printf("::::::::::::::::::::::::::::::::::::::::\n");
        strct = strct->next;
    }
}

char *find_value(char *key)
{
    t_env *head = g_global->env;

    while (head)
    {
        if (ft_strcmp(head->key, key) == 0)
            return (head->value);
        else
            head = head->next;
    }
    return NULL;
}
void initialise_struct(char **env)
{
    g_global = malloc(sizeof(t_global));
    memset(g_global, 0, sizeof(t_global));
    g_global->flag_env = 1;
    g_global->exit_status = 0;
    parse_env_var(env);
    g_global->save_fd_int = dup(STDIN_FILENO);
    g_global->save_fd_out = dup(STDOUT_FILENO);
    g_global->pwd = ft_strdup(find_value("PWD"));
    g_global->oldpwd = ft_strdup(find_value("OLDPWD"));
    g_global->underscore = ft_strdup(NULL);
}

void ft_handl_ctrl_d(void)
{
    int exit_s;

    free_list(&g_global->env);
    if (g_global->pwd)
        free(g_global->pwd);
    if (g_global->oldpwd)
        free(g_global->oldpwd);
    if (g_global->underscore)
        free(g_global->underscore);
    // free_minishell(&g_global->strct);
    close(g_global->save_fd_int);
    close(g_global->save_fd_out);
    exit_s = g_global->exit_status;
    free(g_global);
    write(1, "exit\n", 6);
    exit(exit_s);
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char *line;
    initialise_struct(env);
    while (1)
    {
        ft_sig_handling();
        line = readline("Minishell$> ");
        if (!line)
        {
            ft_handl_ctrl_d();
        }
        g_global->strct = parce(line);
        if (g_global->strct)
        {
            print(g_global->strct);
            ft_execution(g_global->strct);
            dup2(g_global->save_fd_int, STDIN_FILENO);
            // close(g_global->save_fd_int);
            // close(g_global->save_fd_out);
            add_history(line);
            // if (g_global->pid)
            //     free(g_global->pid);
            // ft_free(g_global->strct->cmd, len_double_str(g_global->strct->cmd));
            free_minishell(&g_global->strct);
            free(g_global->strct);
        }
        if (line)
            free(line);
    }
    ft_free_global();
}
