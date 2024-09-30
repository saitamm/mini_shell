/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:45:29 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/30 09:55:47 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	help_help(char c, bool d_quote)
{
	if ((ft_isalnum(c) || c == '_') || c == '$' || (c == '"' && !d_quote)
		|| c == '?')
		return (1);
	return (0);
}

int	need_expand(char *str, int *pos)
{
	int		i;
	t_flag	flag;

	i = 0;
	flag.s_quote = 0;
	flag.d_quote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		update_quotes(&flag.s_quote, &flag.d_quote, str[i]);
		if (str[i] == '$' && !flag.s_quote && str[i + 1])
		{
			if (help_help(str[i + 1], flag.d_quote))
			{
				*pos = i;
				return (1);
			}
		}
		if (!str[i])
			break ;
		i++;
	}
	return (0);
}

char	*find_str_exp(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$' || ft_isalnum(str[i]) == 2 || str[i] == '?')
		return (ft_substr(str, 0, 1));
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != 95 && !ft_isalnum(str[i]))
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}

char	*expand_str(char *string, int pos)
{
	char	*sub_1;
	char	*sub_2;
	char	*sub_3;
	char	*sub_exp;
	char	*final;

	sub_1 = ft_substr(string, 0, pos);
	sub_3 = find_str_exp(string + pos + 1);
	sub_exp = help_expand(sub_3);
	if (ft_strchr(sub_exp, '"') || ft_strchr(sub_exp, '\''))
		sub_exp = help_quote_exp(sub_exp);
	sub_2 = ft_strjoin(sub_1, sub_exp);
	final = ft_strjoin(sub_2, string + pos + ft_strlen(sub_3) + 1);
	free(sub_1);
    free(sub_3);
    free(sub_2);
	return (final);
}

int	have_to_split(char *str)
{
	int		i;
	t_flag	b;

	i = 0;
	b.s_quote = false;
	b.d_quote = false;
	while (str[i])
	{
		update_quotes(&b.s_quote, &b.d_quote, str[i]);
		if (ft_whitespace(str[i]) && !b.s_quote && !b.d_quote)
			return (1);
		i++;
	}
	return (0);
}
