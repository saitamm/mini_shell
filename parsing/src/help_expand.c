/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:39:51 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/20 10:04:22 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char	*ft_cpy_dolar(char *str)
// {
// 	int	i;
// 	char	*d;

// 	i = 0;
// 	if (str[i] == '$')
// 		return (NULL);
// 	while (str[i] != '$')
// 		i++;
// 	d = malloc((i + 1) * sizeof(char));
// 	if (!d)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != '$')
// 	{
// 		d[i] = str[i];
// 		i++;
// 	}
// 	d[i] = '\0';
// 	return(d);
// }

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
	while (env)
	{
		if (!ft_strncmp(str, env->key, ft_strlen(str)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
