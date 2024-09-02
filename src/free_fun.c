/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:33:19 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/31 09:41:56 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	free_cmd(t_cmd **cmd)
{
	t_cmd	*s;

	while (*cmd)
	{
		s = *cmd;
		free((*cmd)->cmd);
		*cmd = (*cmd)->next;
		free(s);
	}
	*cmd = NULL;
}

void    free_data(t_data **data)
{
	t_data	*k;

	
	while (*data)
	{
		k = (*data);
		free_cmd(&(*data)->command);
		(*data) = (*data)->next;
		free(k);
	}
	*data = NULL;
}