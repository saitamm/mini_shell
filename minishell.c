/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:29:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/04 16:18:49 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_global *g_global = NULL;

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
        line = readline(GOLD "$minishell>" RESET);

        if (!line)
            return 0;
        strct = parce(line);
        if (!strct)
            continue;
        ft_execution(strct, execution_struct);
        add_history(line);
        free(line);
    }
    return (0);
}