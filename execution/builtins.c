/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:44:02 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/01 10:19:54 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_bashlvl(t_minishell *strct)
{
	t_env	*env;
	int		shlvl;
	char	*new_value;

	env = g_global->env;
	if (ft_strcmp(strct->cmd[0], "./minishell") == 0)
	{
		while (env)
		{
			if (ft_strcmp(env->key, "SHLVL") == 0)
			{
				shlvl = ft_atoi(env->value);
				shlvl++;
				if (shlvl == 1000)
					shlvl = 1;
				new_value = malloc(12);
					// Enough space for an int (max 10 digits+ sign+ null terminator)
				if (!new_value)
					return ;
				printf("new_value %d", shlvl);
				free(env->value);
				env->value = ft_itoa(shlvl);
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

void	ft_builtins(t_minishell *strct)
{
	if (!strct || !strct->cmd || !strct->cmd[0])
		return ;
	else if (ft_strcmp(strct->cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(strct->cmd[0], "env") == 0)
		print_env(g_global->env, strct->cmd);
	else if (ft_strcmp(strct->cmd[0], "echo") == 0)
		ft_echo(strct->cmd);
	else if (ft_strcmp(strct->cmd[0], "cd") == 0)
		ft_cd(strct->cmd);
	else if (ft_strcmp(strct->cmd[0], "unset") == 0)
		unset(strct->cmd);
	else if (ft_strcmp(strct->cmd[0], "export") == 0)
		ft_export(strct);
	else if (ft_strcmp(strct->cmd[0], "exit") == 0)
		ft_exit(strct->cmd);
}