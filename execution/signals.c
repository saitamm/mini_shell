/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:06:55 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/04 11:23:58 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_sig_handler(int sig)
{
    (void)sig;
    write(1,"\n",1);
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
}

void ft_sig_handling(void)
{
    signal(SIGQUIT, SIG_IGN); // CTRL + '\'
    signal(SIGINT, ft_sig_handler);
}