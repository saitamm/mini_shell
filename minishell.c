/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:29:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/08/30 11:35:07 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_global *g_global = NULL;

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char    *line;
    t_minishell *strct;
    t_execution *execution_struct = NULL;
    
    execution_struct->ac = ac;
    execution_struct->av = av;
    execution_struct->env = env;

    parse_env_var(env);
    print_list(g_global->env);
    while (1)
    {
        line = readline("$>");
        
        if (!line)
            return 0 ;
        strct = parce(line);
        if (!strct)
            continue;
        ft_execution(strct, execution_struct);
		add_history(line);
        free(line);
    }
    return (0);
}