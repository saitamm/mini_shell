/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:06:55 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/04 15:29:45 by lai-elho         ###   ########.fr       */
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
}

void	ft_sig_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_sigint);
}

//to reset the child
void	handle_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

// for the heardoc use 

static void	_exit_herdoc(int sign)
{
	(void)sign;
	printf("\n");
	rl_replace_line("", 1);
	exit(120);
}

void	child_singal_handler(void)
{
	signal(SIGINT, _exit_herdoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}