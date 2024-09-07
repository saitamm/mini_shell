/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:45:29 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/07 11:33:42 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_dollar(char *str, int *i)
{
	int count;

	count = 0;
	while (str[*i])
	{
		if (str[*i] == '$')
			{
				count++;
				(*i)++;
				while (str[*i] && str[*i] == '$')
				{
					(*i)++;
					count++;
				}
			}
		if (count % 2 == 1)
			return (1);
		(*i)++;
		count = 0;
	}
	return (0);
}
int	need_expand(char *str)
{
	int	i;
	t_flag	flag;

	i = 0;
	flag.s_quote = 0;
	flag.d_quote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		update_quotes(&flag.s_quote, &flag.d_quote, str[i]);
		if (str[i] == '$' && !flag.s_quote)
		{
			if (update_dollar(str, &i))
			{
				if (ft_isalpha(str[i]))
					return (1);
			}
		}
		i++;
	}
	return (0);
}
int	nmbr_dollar(char *str)
{
	int	i;
	t_flag	b;
	int		count;

	i = 0;
	count = 0;
	b.s_quote = false;
	b.d_quote = false;
	while (str[i])
	{
		update_quotes(&b.s_quote, &b.d_quote, str[i]);
		if (!b.s_quote && !b.d_quote && str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*expand_str(char *string)
{
	size_t	i;
	size_t	j;
	char	*sub_1;
	char	*sub_2;
	char 	*sub2_exp;
	t_flag	b;

	i = 0;
	b.s_quote = 0;
	while (string[i])
	{
		update_quotes(&b.s_quote, &b.d_quote, string[i]);
		if (!b.s_quote && string[i] == '$' && ft_isalpha(string[i+1]))
			break;
		i++;
	}
	sub_1 = ft_substr(string, 0, i);
	while (string[i] == '$')
		i++;
	j = 0;
	while (string[i + j])
	{
		if (!ft_isalpha(string[i + j]))
			break;
		j++;
	}
	sub_2 = ft_substr(string+i, 0, j);
	sub2_exp = help_expand(sub_2);
	sub_2 = ft_strjoin(sub_1, sub2_exp);
	sub_2 = ft_strjoin(sub_2, string + i + j);
	free(string);
	return (sub_2);
}



char	**split_str(char *str, int *f)
{
	char	**spl_str;

	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
	{
		*f = 1;
		str = remove_quote(str);
		str = help_pipe_quote_2(str);
		spl_str = malloc(2*sizeof(char *));
		if (!spl_str)
			return (NULL);
		spl_str[0] = ft_strdup(str);
		free(str);
		spl_str[1] = NULL;
		return (spl_str);
	}
	// printf(">>>%s\n", str);
	// str = remove_quote(str);
	str = help_pipe_quote_2(str);
	spl_str = ft_split_whitesp(str);
	return (spl_str);
}