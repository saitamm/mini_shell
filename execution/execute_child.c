/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:04:16 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 13:28:17 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_special(t_minishell *strct)
{
	if (!ft_strcmp(strct->cmd[0], "."))
	{
		write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
		write(2, ": .: filename argument required\n", 33);
		write(2, ".: usage: . filename [arguments]", 33);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(126);
	}
	else if (!ft_strcmp(strct->cmd[0], ".."))
	{
		write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
		write(2, "command not found\n", 19);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(126);
	}
}

void	help_2_execute_child(t_minishell *strct)
{
	char	*path;
	char	**env_exc;
	char	*h_ex;

	handle_special(strct);
	h_ex = help_expand("PATH");
	path = get_path(h_ex, strct->cmd[0]);
	if (!path)
		free_6(strct, path, h_ex);
	free(h_ex);
	ft_bashlvl(strct);
	env_exc = env_to_array(g_global->env);
	if (execve(path, strct->cmd, env_exc) == -1)
		free_7(strct, path, env_exc);
}

void	help_execute_child(t_minishell *strct)
{
	char	**spl;
	int		l;

	spl = ft_split(strct->cmd[0], ' ');
	if (!spl[0] || strct->cmd[0][0] == '\0')
		free_2(strct, spl);
	if (ft_strchr(strct->cmd[0], '/'))
	{
		if (access(strct->cmd[0], X_OK) == -1)
		{
			l = open(strct->cmd[0], X_OK);
			if (l == -1)
				free_3(strct, spl);
			else
				free_4(strct, spl, l);
			close(l);
		}
		if (is_directory(strct->cmd[0]))
			free_5(strct, spl);
	}
	ft_free(spl, len_double_str(spl));
	help_2_execute_child(strct);
}

int	execute_child(t_minishell *strct)
{
	handle_signals();
	if (strct->cmd[0] == NULL)
		free_0();
	if (!strct->cmd[0])
		free_0();
	else
		help_execute_child(strct);
	exit(0);
}
