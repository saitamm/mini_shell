/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:11:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/05 00:56:55 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_home_path(void)
{
	t_env	*head;

	head = g_global->env;
	while (head)
	{
		if (ft_strcmp(head->key, "HOME") == 0)
		{
			return (ft_strdup(head->value));
		}
		else
			head = head->next;
	}
	return (NULL);
}

void	ft_find_current_pwd(void)
{
	t_env	*head;

	head = g_global->env;
	while (g_global->env)
	{
		if (ft_strcmp(g_global->env->key, "PWD") == 0)
		{
			free(g_global->pwd);
			g_global->pwd = ft_strdup(g_global->env->value);
			break ;
		}
		else
			g_global->env = g_global->env->next;
	}
	g_global->env = head;
}
void	help_1_ft_change_curr_and_old_path(char *new_path)
{
	free(g_global->env->value);
	g_global->env->value = ft_strdup(g_global->pwd);
	free(g_global->pwd);
	g_global->pwd = ft_strdup(new_path);
}
void	help_2_ft_change_curr_and_old_path(char *new_path)
{
	free(g_global->env->value);
	g_global->env->value = ft_strdup(new_path);
	free(g_global->pwd);
	g_global->pwd = ft_strdup(new_path);
}

void	ft_change_curr_and_old_path(char *new_path)
{
	t_env	*head;

	head = g_global->env;
	while (g_global->env)
	{
		if (ft_strcmp(g_global->env->key, "OLDPWD") == 0)
		{
			help_1_ft_change_curr_and_old_path(new_path);
			break ;
		}
		else
			g_global->env = g_global->env->next;
	}
	while (g_global->env)
	{
		if (ft_strcmp(g_global->env->key, "PWD") == 0)
		{
			help_2_ft_change_curr_and_old_path(new_path);
			break ;
		}
		else
			g_global->env = g_global->env->next;
	}
	g_global->env = head;
}

int	ft_cd(char **Path)
{
	char	cwd[1024];
	char	*home_path;

	home_path = NULL;
	if (!Path || !Path[1])
	{
		home_path = find_home_path();
		if (!home_path)
		{
			write(2, "MInishell : cd : HOME not set\n", 31);
			return (1);
		}
		ft_find_current_pwd();
		ft_change_curr_and_old_path(home_path);
		if (chdir(home_path) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				ft_find_current_pwd();
				ft_change_curr_and_old_path(cwd);
			}
			else
				perror("getcwd error");
		}
		else
			perror(Path[0]);
		free(home_path);
		return (0);
	}
	if (Path != NULL)
	{
		if (Path[2])
		{
			write(2, "Minishell: cd: too many arguments\n", 35);
			return (1);
		}
		if (ft_strcmp(Path[1], "~") == 0 || ft_strcmp(Path[1], "--") == 0)
			home_path = find_home_path();
		if (chdir(Path[1]) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				ft_find_current_pwd();
				ft_change_curr_and_old_path(cwd);
			}
			else
				perror("getcwd error");
		}
		else
		{
			perror(Path[0]);
			free(home_path);
			return (1);
		}
		free(home_path);
	}
	return (0);
}
