/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:12:52 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/29 21:35:19 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_file(char *str)
{
	int		i;
	char	*file;
	char	c;
	int		flag;

	i = 0;
	if (str[i] == '<' || str[i] == '>')
		str++;
	while (ft_whitespace(str[i]) == 1)
		str++;
	flag = 1;
	if (str[i] == '\'' || str[i] == '\"')
	{
		flag = 0;
		c = str[i++];
	}
	while ((!ft_whitespace(str[i]) && str[i] && flag) || (str[i] && str[i] != c && !flag))
		i++;
	if (flag == 0)
		i++;
	file = malloc((i+1) * sizeof(char));
	if (!file)
		return (NULL);
	i = 0;
	if (flag == 0)
	{
		file[i] = str[i];
		i++;
	}
	
	while ((!ft_whitespace(str[i]) && str[i] && flag) || (str[i] && str[i] != c && !flag))
	{
		file[i] = str[i];
		i++;
	}
	if (str[i] == c && str[i])
		file[i++] = c;
	file[i] = '\0';
	return (file);
}

char	*help_file(char *str, t_file **s, char *src)
{
	char	**spl_str;
	int		f;

	while (need_expand(src) && (*s)->file_type != HER_DOC)
		src = expand_str(src);
	spl_str = split_str(src, &f);
	if (len_double_str(spl_str) > 1 && (*s)->file_type != HER_DOC)
	{
		src = str;
		(*s)->flag = AMB;
		return (src);
	}
	if ((*s)->file_type == 2 && f == 1)
		(*s)->flag = 2;
	return (spl_str[0]);
}
