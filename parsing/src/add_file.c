/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:37:58 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/02 13:05:02 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_her_append(int *i, t_data **s, char *str)
{
	char	*string;
	t_file	*new;

	*i = *i + 2;
	//str makhas tfreea
	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		return ;
	string = ft_file(str + (*i));
	if (str[*i - 1] == '<')
		new->file_type = HER_DOC;
	else
		new->file_type = APPEND;
	ft_lstadd_file(&(*s)->files, string, new);
	*i = *i + ft_skip(str + *i) + ft_strlen(string);
	free(string);
}

int	append_her_doc(char a, char b)
{
	if (a == '<' && a == b)
		return (1);
	else if (a == '>' && a == b)
		return (1);
	return (0);
}

void	add_infile(int *i, t_data **s, char *str)
{
	char	*file_cmd;
	t_file	*new;

	*i = (*i) + 1;
	file_cmd = ft_file(str + (*i));
	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		return ;
	new->file_type = IN;
	ft_lstadd_file(&(*s)->files, file_cmd, new);
	(*i) = (*i) + ft_skip(str + (*i)) + ft_strlen(file_cmd);
	free(file_cmd);
}

void	add_outfile(int *i, t_data **s, char *str)
{
	char	*file_cmd;
	t_file	*new;

	*i = (*i) + 1;
	file_cmd = ft_file(str + (*i));
	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		return ;
	new->file_type = OUT;
	ft_lstadd_file(&(*s)->files, file_cmd, new);
	(*i) = (*i) + ft_skip(str + (*i)) + ft_strlen(file_cmd);
	free(file_cmd);
}

void	add_file(int *i, char *str, t_data **s)
{
	//str makhas tfreea
	if (append_her_doc(str[*i], str[(*i) + 1]))
		add_her_append(i, s, str);
	else if (str[*i] == '<')
		add_infile(i, s, str);
	else if (str[*i] == '>')
		add_outfile(i, s, str);
}
