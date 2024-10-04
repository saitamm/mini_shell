/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:21:18 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/30 21:59:59 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list(t_env **m_shell)
{
	t_env	*k;

	if (!m_shell)
		return ;
	while (*m_shell)
	{
		k = *m_shell;
		if (k->key)
		{
			free(k->key);
			k->key = NULL;
		}
		if (k->value)
		{
			free(k->value);
			k->value = NULL;
		}
		*m_shell = (*m_shell)->next;
		free(k);
	}
	*m_shell = NULL;
}
void	ft_free_global(void)
{
	if (g_global->env)
		free_list(&g_global->env);
	if (g_global->pwd)
		free(g_global->pwd);
	if (g_global->oldpwd)
		free(g_global->oldpwd);
	if (g_global->underscore)
		free(g_global->underscore);
	// if (g_global->pid)
	// 	free(g_global->pid);

	// free(g_global);
}