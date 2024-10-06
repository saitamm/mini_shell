/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:12:52 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/06 11:29:27 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_file(char *str)
{
	char	*file;
	t_flag	b;
	int		i;

	i = 0;
	b.s_quote = 0;
	b.d_quote = 0;
	while (ft_whitespace(str[0]))
		str++;
	while (str[i])
	{
		update_quotes(&b.s_quote, &b.d_quote, str[i]);
		if (!b.s_quote && !b.d_quote && ft_whitespace(str[i]))
			break ;
		if (str[i] == '<' && !b.s_quote && !b.d_quote)
			break ;
		if (str[i] == '>' && !b.s_quote && !b.d_quote)
			break ;
		if (str[i])
			i++;
	}
	file = ft_substr(str, 0, i);
	return (file);
}

char	*help_norm_expand(char *string, t_file *s)
{
	int		pos;
	char	*new_src;

	pos = 0;
	while (need_expand(string, &pos) && s->file_type != HER_DOC)
	{
		new_src = expand_str(string, pos);
		free(string);
		string = ft_strdup(new_src);
		free(new_src);
	}
	return (string);
}

char	*help_file(char *str, t_file **s, char *src)
{
	char	**spl_str;
	int		pos;

	pos = 0;
	src = help_norm_expand(src, *s);
	spl_str = split_str(src, &pos);
	if ((len_double_str(spl_str) > 1 && (*s)->file_type != HER_DOC) || !src)
	{
		free(src);
		src = ft_strdup(str);
		(*s)->flag = AMB;
		return (ft_free(spl_str, len_double_str(spl_str)), src);
	}
	if ((*s)->file_type == HER_DOC)
	{
		free(src);
		if (pos == 1)
			(*s)->flag = Q_HER;
		src = create_file_herdoc(spl_str[0], (*s)->flag);
		return (ft_free(spl_str, len_double_str(spl_str)), src);
	}
	free(src);
	src = ft_strdup(spl_str[0]);
	return (ft_free(spl_str, len_double_str(spl_str)), src);
}

char	*skip_red(char *str)
{
	int		i;
	bool	s_flag;
	bool	d_flag;

	i = 0;
	s_flag = false;
	d_flag = false;
	str = ft_strtrim(str, "\n\t\f\v\r ");
	if (str[i] != '>' && str[i] != '<')
		return (str);
	str++;
	while (ft_whitespace(str[i]))
		str++;
	while (str[i])
	{
		if (str[i] == '\'' && !d_flag)
			s_flag = !s_flag;
		if (str[i] == '\"' && !s_flag)
			d_flag = !d_flag;
		if (ft_whitespace(str[i]) && !s_flag && !d_flag)
			return (str);
		str++;
	}
	return (NULL);
}
