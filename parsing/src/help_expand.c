/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:39:51 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/12 12:46:50 by sait-amm         ###   ########.fr       */
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
		return (ft_strdup(g_global->pwd));
	if (!ft_strncmp(str, "OLDPWD", 6))
		return (ft_strdup(g_global->oldpwd));
	if (!ft_strncmp(str, "_", 1))
		return (ft_strdup(g_global->underscore));
	else if (!ft_strncmp(str, "?", 1))
		return (ft_itoa(g_global->exit_status));
	while (env)
	{
		if (!ft_strncmp(str, env->key, ft_strlen(str)))
			return (ft_strdup(env->value));
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

int	special(int r, char *str)
{
	int		i;
	char	**spl;
	char	*sub;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	sub = ft_substr(str, 0, i);
	spl = ft_split_whitesp(sub);
	if (r && len_double_str(spl) == 1)
		return (ft_free(spl, len_double_str(spl)), free(sub), 1);
	ft_free(spl, len_double_str(spl));
	free(sub);
	return (0);
}

char	**split_str(char *str, int *f, int r)
{
	char	**spl_str;
	char	*temp;

	if (!str)
		return (NULL);
	if (!have_to_split(str) || special(r, str))
	{
		if (ft_strchr(str, '"') || ft_strchr(str, '\''))
			*f = 1;
		temp = remove_quote(str);
		temp = help_pipe_quote_2(temp);
		spl_str = malloc(2 * sizeof(char *));
		if (!spl_str)
			return (free(temp), NULL);
		spl_str[0] = ft_strdup(temp);
		spl_str[1] = NULL;
		return (free(temp), spl_str);
	}
	str = help_space(str);
	temp = remove_quote(str);
	spl_str = ft_split_whitesp(temp);
	free(temp);
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
