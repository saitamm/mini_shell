/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:29:23 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/07 12:20:18 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_global	*g_global = NULL;

char	*find_value(char *key)
{
	t_env	*head;

	head = g_global->env;
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head->value);
		else
			head = head->next;
	}
	return (NULL);
}

void	initialise_struct(char **env)
{
	g_global = malloc(sizeof(t_global));
	memset(g_global, 0, sizeof(t_global));
	g_global->flag_env = 1;
	g_global->exit_status = 0;
	g_global->pid = 0;
	parse_env_var(env);
	g_global->save_fd_int = dup(STDIN_FILENO);
	g_global->save_fd_out = dup(STDOUT_FILENO);
	g_global->pwd = ft_strdup(find_value("PWD"));
	g_global->oldpwd = ft_strdup(find_value("OLDPWD"));
	g_global->underscore = ft_strdup(NULL);
}

void	ft_handl_ctrl_d(void)
{
	int	exit_s;

	free_list(&g_global->env);
	if (g_global->pwd)
		free(g_global->pwd);
	if (g_global->oldpwd)
		free(g_global->oldpwd);
	if (g_global->underscore)
		free(g_global->underscore);
	close(g_global->save_fd_int);
	close(g_global->save_fd_out);
	exit_s = g_global->exit_status;
	free(g_global);
	write(1, "exit\n", 6);
	exit(exit_s);
}

void	norm_main(char *line)
{
	add_history(line);
	free_minishell(&g_global->strct);
	free(g_global->strct);
	dup2(g_global->save_fd_int, STDIN_FILENO);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	initialise_struct(env);
	while (1)
	{
		ft_sig_handling();
		line = readline("Minishell$> ");
		if (!line)
			ft_handl_ctrl_d();
		g_global->sig_herdoc = 0;
		g_global->strct = parce(line);
		print(g_global->strct);
		if (her_doc_sig(line))
		{
			if (g_global->strct)
			{
				ft_execution(g_global->strct);
				norm_main(line);
			}
		}
		free(line);
	}
	ft_free_global();
}
