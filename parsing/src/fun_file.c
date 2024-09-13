/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:12:52 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/13 11:16:36 by sait-amm         ###   ########.fr       */
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
			break;
		i++;
	}
	file = ft_substr(str, 0, i);
	return (file);
}

char	*help_file(char *str, t_file **s, char *src)
{
	char	**spl_str;
	int		f;
	int		pos;

	f = 0;
	pos = 0;
	while (need_expand(src, &pos) && (*s)->file_type != HER_DOC)
		src = expand_str(src, pos);
	spl_str = split_str(src, &f);
	if ((len_double_str(spl_str) > 1 && (*s)->file_type != HER_DOC) || !spl_str[0])
	{
		src = str;
		(*s)->flag = AMB;
		ft_free(spl_str, len_double_str(spl_str));
		return (src);
	}
	if ((*s)->file_type == HER_DOC)
	{
		if ( f == 1)
			(*s)->flag = 2;
		src = create_file_herdoc(str, (*s)->flag);
		ft_free(spl_str, len_double_str(spl_str));
		return (src);
	}
	return (spl_str[0]);
}
