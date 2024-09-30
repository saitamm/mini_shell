/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/30 21:58:48 by sait-amm         ###   ########.fr       */
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
void	execute_child(t_minishell *strct)
{
	char	*path;
	char	**env_exc;

	if (!strct || !strct->cmd || !strct->cmd[0])
	{
		return ;
	}
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
	else
	{
		if (!ft_split(strct->cmd[0], ' ')[0] || strct->cmd[0][0] == '\0')
		{
			write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
			write(2, ": command not found\n", 21);
			g_global->exit_status = 127;
			ft_free_global();
			exit(g_global->exit_status);
		}
		if (ft_strchr(strct->cmd[0], '/'))
		{
			if (access(strct->cmd[0], X_OK) == -1)
			{
				if (open(strct->cmd[0], X_OK) == -1)
				{
					perror(strct->cmd[0]);
					g_global->exit_status = 127;
					ft_free_global();
					exit(g_global->exit_status);
				}
				else
				{
					perror(strct->cmd[0]);
					g_global->exit_status = 126;
					ft_free_global();
					exit(g_global->exit_status);
				}
			}
			if (is_directory(strct->cmd[0]))
			{
				write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
				write(2, ": is a directory\n", 18);
				g_global->exit_status = 126;
				ft_free_global();
				exit(g_global->exit_status);
			}
		}
		path = get_path(help_expand("PATH"), strct->cmd[0]);
		if (!path)
		{
			write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
			write(2, ": command not found\n", 21);
			g_global->exit_status = 127;
			ft_free_global();
			exit(g_global->exit_status);
		}
		ft_bashlvl(strct);
		env_exc = env_to_array(g_global->env);
		if (execve(path, strct->cmd, env_exc) == -1)
		{
			ft_free(strct->cmd,len_double_str(strct->cmd));
			free(path);
			ft_free(env_exc, len_double_str(env_exc));
		}
	}
	g_global->exit_status = 0;
	ft_free_global();
	exit(0);
}

void	ft_exec_child(t_minishell *strct)
{
	redirection(strct);
	execute_child(strct);
	close(g_global->fd_pipe[0]);
	close(g_global->fd_pipe[1]);
}

int	ft_lstsize_minishell(t_minishell *lst)
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
int	ft_infile_built(t_minishell *strct)
{
	int	infile_fd;

	if (strct->files->flag == AMB)
	{
		write(2, "Minishell:", 11);
		write(2, strct->files->file, ft_strlen(strct->files->file));
		write(2, ": ambiguous redirect\n", 22);
		g_global->exit_status = 1;
		return (1);
	}
	infile_fd = open(strct->files->file, O_RDONLY);
	if (infile_fd == -1)
	{
		if (access(strct->files->file, F_OK) != 0)
		{
			write(2, "Minishell:", 11);
			perror(strct->files->file);
			g_global->exit_status = 1;
			return (1);
		}
		else if (access(strct->files->file, R_OK) != 0)
		{
			write(2, "Minishell:", 11);
			perror(strct->files->file);
			g_global->exit_status = 1;
			return (1);
		}
		perror("Error opening file\n");
		g_global->exit_status = 1;
		return (1);
	}
	if (ft_strcmp(strct->files->file, "/dev/stdin"))
	{
		if (dup2(infile_fd, STDIN_FILENO) == -1)
		{
			perror("Error in dup2\n");
			g_global->exit_status = 1;
			close(infile_fd);
			return (1);
		}
	}
	close(infile_fd);
	return (0);
}

int	redirection_buils(t_minishell *strct)
{
	t_minishell	*head;
	int			flag;

	head = strct;
	flag = 0;
	while (head && head->files)
	{
		if (head->files->file_type == IN || head->files->file_type == HER_DOC)
		{
			if (ft_infile_built(head))
				return (1);
		}
		else if (head->files->file_type == 1)
			ft_outfile(head);
		else if (head->files->file_type == 3)
		{
			flag = 1;
			ft_append(head);
		}
		head->files = head->files->next;
	}
	return (0);
}

void	ft_execution(t_minishell *strct)
{
	int	status;
	int	st;
	int	size;
	int	i;

	size = ft_lstsize_minishell(strct);
	i = 0;
	g_global->pid = malloc(size * sizeof(int));
	if (size == 1 && is_built(strct->cmd[0]))
	{
		if (redirection_buils(strct))
			return ;
		ft_builtins(strct);
		ft_underscore(strct);
		dup2(g_global->save_fd_out, STDOUT_FILENO);
		dup2(g_global->save_fd_int, STDIN_FILENO);
	}
	else
	{
		while (strct)
		{
			if (pipe(g_global->fd_pipe) == -1)
			{
				perror("pipe error");
				ft_free_global();
				exit(1);
			}
			else
			{
				g_global->pid[i] = fork();
				if (g_global->pid[i] == 0)
					ft_exec_child(strct);
			}
			close(g_global->fd_pipe[1]);
			dup2(g_global->fd_pipe[0], STDIN_FILENO);
			close(g_global->fd_pipe[0]);
			ft_underscore(strct);
			g_global->exit_status = 0;
			strct = strct->next;
			i++;
		}
		i = 0;
		while (i < size)
		{
			waitpid(g_global->pid[i], &status, 0);
			st = status >> 8;
			g_global->exit_status = st;
			i++;
		}
	}
	free(g_global->pid);
}
