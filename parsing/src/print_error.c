/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:01:23 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/11 20:25:29 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	synt_error(char *str, char c)
{
	write(2, str, ft_strlen(str));
	write(2, " '", 2);
	write(2, &c, 1);
	write(2, "'", 1);
	write(2, "\n", 1);
	g_global->exit_status = 2;
	return (1);
}
