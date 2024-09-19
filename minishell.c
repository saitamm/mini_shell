/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:29:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/19 11:36:59 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_global *g_global = NULL;

void    print(t_minishell *strct)
{
     t_file   *tmp2;
        while (strct != NULL)
        {
        int i = 0;
        tmp2 = strct->files;
        while (strct->cmd[i])
        {
            printf("command %d >>>> *%s*\n",i,  strct->cmd[i]);
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
int main(int ac, char **av, char **env)
{
    char *line;
    t_minishell *strct;
    t_execution *execution_struct = NULL;
    g_global = malloc(sizeof(t_global));
    execution_struct = malloc(sizeof(t_execution));
    if (!execution_struct)
        return (0);
    execution_struct->ac = ac;
    execution_struct->av = av;
    execution_struct->env = env;
    g_global->env = NULL;
    parse_env_var(env);
    while (1)
    {
        line = readline("Minishell$>" );
        if (!line)
            return 0;
        strct = parce(line);
        if (!strct)
            continue;
        print(strct);
        // ft_execution(strct);
        add_history(line);
        free(line);
    }
    return (0);
}
