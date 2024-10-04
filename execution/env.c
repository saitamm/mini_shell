/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:49:44 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/02 14:58:55 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_env(t_env *head, char **cmd)
{
	t_env	*temp;

	temp = head;
	if (cmd[1])
		return 0;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PATH") && !g_global->flag_env)
			temp = temp->next;
		else if (temp->key && temp->value)
		{
			printf("%s=%s\n", temp->key, temp->value);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	return(0);
}
