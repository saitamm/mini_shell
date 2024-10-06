/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:11:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 22:30:46 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	help_cd_home(char **Path)
{
	char	*home_path;
	char	cwd[1024];

	home_path = find_home_path();
	if (!home_path)
		return (write(2, "Minishell : cd : HOME not set\n", 31), 1);
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

void	help_cd_path(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_find_current_pwd();
		ft_change_curr_and_old_path(cwd);
	}
	else
		perror("getcwd error");
}

int	ft_cd(char **Path)
{
	char	*home_path;

	home_path = NULL;
	if (!Path || !Path[1] || (ft_strcmp(Path[1], "~") == 0 || ft_strcmp(Path[1], "--") == 0))
		return (help_cd_home(Path));
	if (Path != NULL)
	{
		if (Path[2])
			return (write(2, "Minishell: cd: too many arguments\n", 35), 1);
		if (chdir(Path[1]) == 0)
			help_cd_path();
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
