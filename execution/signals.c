/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:06:55 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/12 18:18:41 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// parent sig
static void	ft_handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_global->exit_status = 130;
}

void	ft_sig_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_sigint);
}

void	sigint(int sig)
{
	(void)sig;
	rl_clear_history();
	exit(130);
}

void	sigquit(int sig)
{
	(void)sig;
	rl_clear_history();
	exit(131);
}

// to reset the child
void	handle_signals(void)
{
	signal(SIGQUIT, sigquit);
	signal(SIGINT, sigint);
}
