/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:22:58 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 10:26:31 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_fun_norm(char *cmd, char **str)
{
	if (cmd[0] == 92 || cmd[0] == 47)
		cmd_is_path(str, cmd, 1);
	if ((!str && access(cmd, X_OK) == -1))
		error_fun(cmd, 127);
}

char	*find_in_paths(char **str, char *w_path)
{
	char	*path;
	int		i;

	i = 0;
	while (str && str[i])
	{
		path = ft_strjoin(str[i++], w_path);
		if (access(path, X_OK) == 0)
		{
			ft_free(str, len_double_str(str));
			return (path);
		}
		free(path);
	}
	ft_free(str, len_double_str(str));
	return (NULL);
}

char	*find_env_slash(char *envp)
{
	while (envp && *envp != '/')
		envp++;
	return (envp);
}

char	*get_path(char *envp, char *cmd)
{
	char	**str;
	char	*w_path;
	char	*path;

	envp = find_env_slash(envp);
	str = ft_split(envp, ':');
	if (access(cmd, X_OK) == 0 && (cmd[0] == '.' || cmd[0] == '/' || !str))
		return (cmd_is_path(str, cmd, 0));
	else if (cmd[0] == '.')
		ft_fun_norm(cmd, str);
	w_path = ft_strjoin("/", cmd);
	path = find_in_paths(str, w_path);
	free(w_path);
	return (path);
}
