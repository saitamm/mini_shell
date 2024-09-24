/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:39:51 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/23 12:49:36 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <string.h>
char	*help_expand(char *str)
{
	t_env	*env;

	env = g_global->env;
	if (!str || str[0] == '\0')
		return (NULL);
	if (!ft_strncmp(str, "PWD", 3))
		return (g_global->pwd);
	if (!ft_strncmp(str, "OLDPWD", 6))
		return (g_global->oldpwd);
	if (!ft_strncmp(str, "_", 1))
		return(g_global->underscore);
	else if (!ft_strncmp(str, "?", 1))
		return(ft_itoa(g_global->exit_status));
	while (env)
	{
		if (!ft_strncmp(str, env->key, ft_strlen(str)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
