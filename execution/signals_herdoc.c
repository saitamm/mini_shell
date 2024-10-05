/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:59:49 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/05 16:57:04 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_her_doc(int signum)
{
	if (signum == SIGINT)
	{
		g_global->sig_herdoc = -1;
		write(2, "\n", 1);
		close(0);
	}
}

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
