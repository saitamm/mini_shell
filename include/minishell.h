/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:30:09 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/07 09:16:24 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "execution.h"
#include "parting.h"

typedef struct s_global
{
    t_env   *env;
}           t_global;

extern t_global *g_global;

void ft_execution(t_minishell *strct);
void	ft_export(t_minishell *strct);

#endif