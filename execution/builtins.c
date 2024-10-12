/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:44:02 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/12 17:50:28 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_bashlvl(t_minishell *strct)
{
	t_env	*env;
	char	*new_value;

	env = g_global->env;
	if (ft_strcmp(strct->cmd[0], "./minishell") == 0)
	{
		while (env)
		{
			if (ft_strcmp(env->key, "SHLVL") == 0)
			{
				g_global->shelvl = ft_atoi(env->value);
				g_global->shelvl++;
				if (g_global->shelvl == 1000)
					g_global->shelvl = 1;
				new_value = malloc(12);
				if (!new_value)
					return ;
				free(env->value);
				env->value = ft_itoa(g_global->shelvl);
				return ;
			}
			env = env->next;
		}
	}
}

void	ft_underscore(t_minishell *strct)
{
	char	**cmd;
	int		i;

	cmd = strct->cmd;
	i = 0;
	while (cmd[i])
	{
		if (g_global->underscore)
			free(g_global->underscore);
		g_global->underscore = ft_strdup(cmd[i]);
		if (cmd[i])
			i++;
	}
}

int	is_built(char *str)
{
	if (!str || !str || !str)
		return (0);
	if (!ft_strcmp(str, "exit") || !ft_strcmp(str, "export") || !ft_strcmp(str,
			"cd"))
		return (1);
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "unset") || !ft_strcmp(str,
			"echo"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	return (0);
}

int	ft_builtins(t_minishell *strct)
{
	if (!strct || !strct->cmd || !strct->cmd[0])
		return (0);
	else if (ft_strcmp(strct->cmd[0], "pwd") == 0)
		return (g_global->exit_status = ft_pwd());
	else if (ft_strcmp(strct->cmd[0], "env") == 0)
		return (g_global->exit_status = print_env(g_global->env, strct->cmd));
	else if (ft_strcmp(strct->cmd[0], "echo") == 0)
		return (g_global->exit_status = ft_echo(strct->cmd));
	else if (ft_strcmp(strct->cmd[0], "cd") == 0)
		return (g_global->exit_status = ft_cd(strct->cmd));
	else if (ft_strcmp(strct->cmd[0], "unset") == 0)
		return (g_global->exit_status = unset(strct->cmd));
	else if (ft_strcmp(strct->cmd[0], "export") == 0)
	{
		ft_export(strct);
		return (g_global->exit_status);
	}
	else if (ft_strcmp(strct->cmd[0], "exit") == 0)
		return (g_global->exit_status = ft_exit(strct->cmd));
	return (-1);
}
