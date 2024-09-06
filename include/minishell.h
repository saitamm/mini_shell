/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:30:09 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/06 23:25:27 by lai-elho         ###   ########.fr       */
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