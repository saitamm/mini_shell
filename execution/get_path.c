/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:22:58 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/29 09:25:40 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_fun(char *str, int h)
{
	perror(str);
	exit(h);
}
int	ft_lstsize_3(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
char	**env_to_array(t_env *env)
{
	int		size;
	char	**cmd;
	int		i;
	t_env *tmp;

	size = ft_lstsize_3(env);
	tmp = env;
	cmd = malloc((size + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (tmp)
	{
		cmd[i] = ft_strjoin(tmp->key, "=");
        cmd[i] = ft_strjoin(cmd[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
void	ft_double_free(char **str, char *cmd_1, char *w_path)
{
	ft_free(str, len_double_str(str));
	free(cmd_1);
	free(w_path);
}
char	*cmd_is_path(char **str, char *cmd_1, int flag)
{
	char	*path;

	path = NULL;
	if (flag == 0)
	{
		path = ft_strdup(cmd_1);
		if (str)
			ft_free(str, len_double_str(str));
	}
	else
	{
		perror(cmd_1);
		ft_free(str, len_double_str(str));
		exit(127);
	}
	return (path);
}

void	ft_fun_norm(char *cmd, char **str)
{
	if (cmd[0] == 92 || cmd[0] == 47)
		cmd_is_path(str, cmd, 1);
	if ((!str && access(cmd, X_OK) == -1))
		error_fun(cmd, 127);
}

char	*get_path(char *envp, char *cmd)
{
	char	**str;
	int		i;
	char	*path;
	char	*w_path;

	i = 0;
	while (envp && envp[i] != '/')
		envp++;
	str = ft_split(envp, ':');
	if (access(cmd, X_OK) == 0 && (cmd[0] == '.'
		|| cmd[0] == '/' || !str))
		return (cmd_is_path(str, cmd, 0));
	else
		ft_fun_norm(cmd, str);
	w_path = ft_strjoin("/", cmd);
	while (str && str[i])
	{
		path = ft_strjoin(str[i++], w_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}