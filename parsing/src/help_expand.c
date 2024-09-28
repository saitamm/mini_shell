/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:39:51 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/28 15:35:03 by sait-amm         ###   ########.fr       */
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
		return (g_global->underscore);
	else if (!ft_strncmp(str, "?", 1))
		return (ft_itoa(g_global->exit_status));
	while (env)
	{
		if (!ft_strncmp(str, env->key, ft_strlen(str)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**help_pipe_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		help_pipe_quote_2(str[i]);
		i++;
	}
	return (str);
}

char	**split_str(char *str, int *f)
{
	char	**spl_str;
	char	*temp;

	if (!str)
		return (NULL);
	if (!have_to_split(str))
	{
		*f = 1;
		temp = ft_strdup(str);
		temp = remove_quote(temp);
		temp = help_pipe_quote_2(temp);
		spl_str = malloc(2 * sizeof(char *));
		if (!spl_str)
			return (NULL);
		spl_str[0] = ft_strdup(temp);
		spl_str[1] = NULL;
		return (spl_str);
	}
	str = help_space(str);
	str = remove_quote(str);
	spl_str = ft_split_whitesp(str);
	help_pipe_double(spl_str);
	return (spl_str);
}

char	*help_space(char *str)
{
	int		i;
	t_flag	d;

	d.s_quote = 0;
	d.d_quote = 0;
	i = 0;
	while (str[i])
	{
		update_quotes(&d.s_quote, &d.d_quote, str[i]);
		if (ft_whitespace(str[i]) && (d.s_quote || d.d_quote))
			str[i] = str[i] * (-1);
		i++;
	}
	return (str);
}
