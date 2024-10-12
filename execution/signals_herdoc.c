/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:59:49 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/12 18:18:04 by sait-amm         ###   ########.fr       */
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
