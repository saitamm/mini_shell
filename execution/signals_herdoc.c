/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:59:49 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/05 04:23:03 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
