/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:04 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/06 11:41:50 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_directory(const char *path)
{
	struct stat path_stat;

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

char **ft_execve_arg(char **str)
{
	char **argv;
	int i;

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

void handle_special(t_minishell *strct)
{
	if (!ft_strcmp(strct->cmd[0], "."))
	{
		write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
		write(2, ": .: filename argument required\n", 33);
		write(2, ".: usage: . filename [arguments]", 33);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(126);
	}
	else if (!ft_strcmp(strct->cmd[0], ".."))
	{
		write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
		write(2, "command not found\n", 19);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(126);
	}
}
int execute_child(t_minishell *strct)
{
	char *path;
	char **env_exc;
	int ex;
	char **spl;
	int l;
	char *h_ex;

	ex = 0;
	handle_signals();
	if (strct->cmd[0] == NULL)
	{
		free_minishell(&g_global->strct);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		free(g_global->pid);
		ft_free_global();
		free(g_global);
		exit(0);
	}
	if (!strct->cmd[0])
	{
		free_minishell(&g_global->strct);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		free(g_global->pid);
		ft_free_global();
		free(g_global);
		exit(0);
	}
	if (ft_strcmp(strct->cmd[0], "pwd") == 0)
	{
		ex = ft_pwd();
		free_minishell(&g_global->strct);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		free(g_global->pid);
		ft_free_global();
		free(g_global);
		exit(ex);
	}
	else if (ft_strcmp(strct->cmd[0], "env") == 0)
	{
		ex = print_env(g_global->env, strct->cmd);
		free_minishell(&g_global->strct);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		free(g_global->pid);
		ft_free_global();
		free(g_global);
		exit(ex);
	}
	else if (ft_strcmp(strct->cmd[0], "echo") == 0)
	{
		ex = ft_echo(strct->cmd);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(ex);
	}
	else if (ft_strcmp(strct->cmd[0], "cd") == 0)
	{
		ex = ft_cd(strct->cmd);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(ex);
	}
	else if (ft_strcmp(strct->cmd[0], "unset") == 0)
	{
		ex = unset(strct->cmd);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(ex);
	}
	else if (ft_strcmp(strct->cmd[0], "export") == 0)
	{
		ft_export(strct);
		ex = g_global->exit_status;
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
	}
	else if (ft_strcmp(strct->cmd[0], "exit") == 0)
	{
		ex = ft_exit(strct->cmd);
		free_minishell(&g_global->strct);
		free(g_global->pid);
		close(g_global->save_fd_int);
		close(g_global->save_fd_out);
		ft_free_global();
		free(g_global);
		exit(ex);
	}
	else
	{
		spl = ft_split(strct->cmd[0], ' ');
		if (!spl[0] || strct->cmd[0][0] == '\0')
		{
			write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
			write(2, ": command not found\n", 21);
			free_minishell(&g_global->strct);
			free(g_global->pid);
			close(g_global->save_fd_int);
			close(g_global->save_fd_out);
			ft_free(spl, len_double_str(spl));
			ft_free_global();
			free(g_global);
			exit(127);
		}
		if (ft_strchr(strct->cmd[0], '/'))
		{
			if (access(strct->cmd[0], X_OK) == -1)
			{
				l = open(strct->cmd[0], X_OK);
				if (l == -1)
				{
					perror(strct->cmd[0]);
					free_minishell(&g_global->strct);
					free(g_global->pid);
					close(g_global->save_fd_int);
					close(g_global->save_fd_out);
					ft_free(spl, len_double_str(spl));
					ft_free_global();
					free(g_global);
					exit(127);
				}
				else
				{
					perror(strct->cmd[0]);
					free_minishell(&g_global->strct);
					free(g_global->pid);
					close(g_global->save_fd_int);
					close(g_global->save_fd_out);
					ft_free(spl, len_double_str(spl));
					ft_free_global();
					close(l);
					free(g_global);
					exit(126);
				}
				close(l);
			}
			if (is_directory(strct->cmd[0]))
			{
				write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
				write(2, ": is a directory\n", 18);
				free_minishell(&g_global->strct);
				free(g_global->pid);
				close(g_global->save_fd_int);
				close(g_global->save_fd_out);
				ft_free(spl, len_double_str(spl));
				ft_free_global();
				free(g_global);
				exit(126);
			}
		}
		ft_free(spl, len_double_str(spl));
		handle_special(strct);
		h_ex = help_expand("PATH");
		path = get_path(h_ex, strct->cmd[0]);
		if (!path)
		{
			write(2, strct->cmd[0], ft_strlen(strct->cmd[0]));
			write(2, ": command not found\n", 21);
			close(g_global->save_fd_int);
			close(g_global->save_fd_out);
			free(path);
			free_minishell(&g_global->strct);
			free(g_global->pid);
			ft_free_global();
			free(h_ex);
			free(g_global);
			exit(127);
		}
		free(h_ex);
		ft_bashlvl(strct);
		env_exc = env_to_array(g_global->env);
		if (execve(path, strct->cmd, env_exc) == -1)
		{
			perror(strct->cmd[0]);
			free(path);
			close(g_global->save_fd_int);
			close(g_global->save_fd_out);
			free_minishell(&g_global->strct);
			free(g_global->pid);
			free(g_global);
			ft_free(env_exc, len_double_str(env_exc));
			ft_free_global();
			exit(2);
		}
	}
	exit(ex);
}

void ft_exec_child(t_minishell *strct)
{
	redirection(strct);
	close(g_global->fd_pipe[0]);
	close(g_global->fd_pipe[1]);
	execute_child(strct);
}

int ft_infile_built(t_file *strct)
{
	int infile_fd;

	if (strct->flag == AMB)
	{
		write(2, "Minishell:", 11);
		write(2, strct->file, ft_strlen(strct->file));
		write(2, ": ambiguous redirect\n", 22);
		g_global->exit_status = 1;
		return (1);
	}
	infile_fd = open(strct->file, O_RDONLY);
	if (infile_fd == -1)
	{
		if (access(strct->file, F_OK) != 0)
		{
			write(2, "Minishell:", 11);
			perror(strct->file);
			g_global->exit_status = 1;
			return (1);
		}
		else if (access(strct->file, R_OK) != 0)
		{
			write(2, "Minishell:", 11);
			perror(strct->file);
			g_global->exit_status = 1;
			return (1);
		}
		perror("Error opening file\n");
		g_global->exit_status = 1;
		return (1);
	}
	if (ft_strcmp(strct->file, "/dev/stdin"))
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

int redirection_buils(t_minishell *strct)
{
	t_minishell *head;
	t_file *current_file;

	head = strct;
	// while (head)
	// {
	current_file = head->files;
	while (current_file)
	{
		if (current_file->file_type == IN || current_file->file_type == HER_DOC)
		{
			if (ft_infile_built(current_file))
				return (1);
		}
		else if (current_file->file_type == 1)
		{
			if (ft_outfile_built(current_file))
				return (1);
		}
		else if (current_file->file_type == 3)
		{
			if (ft_append_built(current_file))
				return (1);
		}
		current_file = current_file->next;
	}
	head = head->next;
	// }
	return (0);
}

void ft_execution(t_minishell *strct)
{
	int status;
	int size;
	int i;

	size = ft_lstsize_minishell(strct);
	i = 0;
	if (size == 1 && is_built(strct->cmd[0]))
	{
		if (redirection_buils(strct))
			return;
		ft_builtins(strct);
		ft_underscore(strct);
		dup2(g_global->save_fd_out, STDOUT_FILENO);
		dup2(g_global->save_fd_int, STDIN_FILENO);
	}
	else
	{
		g_global->pid = malloc(size * sizeof(int));
		if (!g_global->pid)
			return;
		while (strct)
		{
			if (pipe(g_global->fd_pipe) == -1)
			{
				perror("pipe error");
				ft_free_global();
				return;
			}
			else
			{
				g_global->pid[i] = fork();
				signal(SIGQUIT, SIG_IGN);
				signal(SIGINT, SIG_IGN);
				if (g_global->pid[i] == 0)
					ft_exec_child(strct);
			}
			close(g_global->fd_pipe[1]);
			dup2(g_global->fd_pipe[0], STDIN_FILENO);
			close(g_global->fd_pipe[0]);
			g_global->exit_status = 0;
			ft_underscore(strct);
			strct = strct->next;
			i++;
		}
		i = 0;
		while (i < size)
		{
			waitpid(g_global->pid[i], &status, 0);
			if (i == size - 1)
			{
				if (WIFEXITED(status))
					g_global->exit_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
				{
					if (WTERMSIG(status) == SIGINT)
					{
						write(1, "\n", 1);
						g_global->exit_status = 130;
					}
					else if (WTERMSIG(status) == SIGQUIT)
					{
						write(1, "Quit (core dumped)\n", 20);
						g_global->exit_status = 131;
					}
				}
			}
			i++;
		}
		free(g_global->pid);
	}
}
