/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:38:26 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 15:18:36 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_5(t_minishell *strct, char **spl)
{
	write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
	write(2, ": is a directory\n", 18);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	ft_free(spl, len_double_str(spl));
	ft_free_global();
	free(g_global);
	exit(126);
}

void	free_6(t_minishell *strct, char *path, char *h_ex)
{
	write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
	write(2, ": command not found\n", 21);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	free(path);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	ft_free_global();
	free(h_ex);
	free(g_global);
	exit(127);
}

void	free_7(t_minishell *strct, char *path, char **env_exc)
{
	perror(strct->cmd[0]);
	free(path);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	free_minishell(&g_global->strct);
	free(g_global->pid);
	ft_free_global();
	free(g_global);
	ft_free(env_exc, len_double_str(env_exc));
	exit(2);
}
