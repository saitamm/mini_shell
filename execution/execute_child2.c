/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:59:33 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/12 18:30:14 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handl_heeeeeeeeeeeeeeeeeeeelp(t_minishell *strct)
{
	if (!ft_strcmp(strct->cmd[0], ".."))
	{
		rl_clear_history();
		write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
		write(2, "command not found\n", 18);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(127);
	}
}

void	handle_special(t_minishell *strct)
{
	if (!ft_strcmp(strct->cmd[0], "."))
	{
		rl_clear_history();
		write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
		write(2, ": .: filename argument required\n", 32);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(2);
	}
	else
		handl_heeeeeeeeeeeeeeeeeeeelp(strct);
}
