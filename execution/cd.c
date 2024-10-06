/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:11:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 10:09:12 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		{
			write(2, "Minishell :", 12);
			perror(Path[0]);
		}
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
			write(2, "Minishell :", 12);
			perror(Path[0]);
			free(home_path);
			return (1);
		}
		free(home_path);
	}
	return (0);
}
