/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:18:43 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 15:28:59 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_fun(char *str, int h)
{
	perror(str);
	exit(h);
}

char	**env_to_array(t_env *env)
{
	int		size;
	char	**cmd;
	int		i;
	char	*tmp_1;
	t_env	*tmp;

	size = ft_lstsize_3(env);
	tmp = env;
	cmd = malloc((size + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (tmp)
	{
		tmp_1 = ft_strjoin(tmp->key, "=");
		cmd[i] = ft_strjoin(tmp_1, tmp->value);
		free(tmp_1);
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
		{
			ft_free(str, len_double_str(str));
		}
	}
	else
	{
		perror(cmd_1);
		ft_free(str, len_double_str(str));
		exit(127);
	}
	return (path);
}
