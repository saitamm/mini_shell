/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:00:18 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 11:08:19 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
	{
		perror("access");
		return (0);
	}
	if (stat(path, &path_stat) != 0)
	{
		perror("stat");
		return (0);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		return (1);
	}
	return (0);
}

char	**ft_execve_arg(char **str)
{
	char	**argv;
	int		i;

	i = 0;
	argv = malloc((len_double_str(str) + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	while (str[i])
	{
		argv[i] = ft_strdup(str[i]);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	ft_exec_child(t_minishell *strct)
{
	redirection(strct);
	close(g_global->fd_pipe[0]);
	close(g_global->fd_pipe[1]);
	execute_child(strct);
}
