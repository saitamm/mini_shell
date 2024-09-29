/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:29:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/28 21:02:23 by sait-amm         ###   ########.fr       */
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

char    *find_value(char *key)
{
    t_env *head = g_global->env;      

    while(head)
    {
        if(ft_strcmp(head->key, key) == 0 )
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
    parse_env_var(env);
    g_global->save_fd_int = dup(STDIN_FILENO);
    g_global->save_fd_out = dup(STDOUT_FILENO);
    g_global->pwd = ft_strdup(find_value("PWD"));
    g_global->oldpwd = ft_strdup(find_value("OLDPWD"));
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char *line;
    initialise_struct(env);
    while (1)
    {
        line = readline("Minishell$> ");
        if (!line)
            return 0;
        g_global->strct = parce(line);
        if (g_global->strct)
        {
            // print(g_global->strct);
            ft_execution(g_global->strct);
            dup2(g_global->save_fd_int, STDIN_FILENO);
            add_history(line);
        }
        if (line)
            free(line);
    }
}
