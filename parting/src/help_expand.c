/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:39:51 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/30 13:24:14 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	*ft_cpy_dolar(char *str)
{
	int	i;
	char	*d;

	i = 0;
	if (str[i] == '$')
		return (NULL);
	while (str[i] != '$')
		i++;
	d = malloc((i + 1) * sizeof(char));
	if (!d)
		return (NULL);
	i = 0;
	while (str[i] != '$')
	{
		d[i] = str[i];
		i++;
	}
	d[i] = '\0';
	return(d);
}

char	*help_expand(char *str)
{
	t_env	*env;

	env = g_global->env;
	while(env)
	{
		if (!ft_strncmp(str, env->key, ft_strlen(str)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
