/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:04:16 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 12:01:16 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	help_2_execute_child(t_minishell *strct, char **spl)
{
	char	*path;
	char	**env_exc;
	char	*h_ex;

	h_ex = help_expand("PATH");
	path = get_path(h_ex, strct->cmd[0]);
	if (!path)
		free_6(strct, spl, path, h_ex);
	free(h_ex);
	ft_bashlvl(strct);
	env_exc = env_to_array(g_global->env);
	ft_free(spl, len_double_str(spl));
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
	help_2_execute_child(strct, spl);
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
