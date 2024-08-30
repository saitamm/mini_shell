/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:50:06 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/30 11:25:31 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_env   *g_env = NULL;

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
	char	*line;
    t_minishell *strct;

    parse_env_var(&g_env, env);
    printf("::%d\n", ac);
    printf("::%s\n", av[0]);
	while (1) {
		line = readline(GOLD "$minishell>" RESET);
		if (line == NULL)
			break;
        strct = parce(line);
        if (!strct)
            continue;
        print(strct);
		add_history(line);
		free(line);
	}
	return 0;
}
