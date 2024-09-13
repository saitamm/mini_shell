/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:59:21 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/13 11:17:08 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	no_red_af(char *str)
{
	int	i;

	i = 0;
	while (ft_whitespace(str[i]))
		i++;
	if (str[i] != '>' && str[i] != '<')
		return (1);
	return (0);
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

int	ft_skip(char *str)
{
	int i;

	i = 0;
	while (ft_whitespace(str[i]) && str[i])
		i++;
	return (i);
}
enum e_type	append_her_doc(char a, char b)
{
	if (a == '<' && a == b)
		return (HER_DOC);
	else if (a == '>' && a == b)
		return (APPEND);
	return (0);
}


void	full_command(t_data **data, char *str)
{
	int		i;
	t_flag	flag;
	t_data *s;
	t_data	*d;
	char	*file_cmd;
	int j = 0;

	
	i = 0;
	flag.s_quote = false;
	flag.d_quote = false;
	s = (t_data *)malloc(sizeof(t_data));
	if (!s)
		return ;
	s->files = NULL;
	s->command = NULL;
	while (str[i])
	{
		while (ft_whitespace(str[i]))
			i++;
		j = 0;
		while (ft_whitespace(str[i+j]))
		{
			update_quotes(&flag.d_quote, &flag.s_quote, str[i+j]);
			j++;
		}
		if (append_her_doc(str[i], str[i+1]) && !flag.s_quote && !flag.d_quote)
		{
			i = i+2;
			t_file *new = (t_file *)malloc(sizeof(t_file));
			if (!new)
				return ;
			file_cmd = ft_file(str+i);
			if (str[i -1] == '<')
				new->file_type = HER_DOC;
			else
				new->file_type = APPEND;
			ft_lstadd_file(&s->files, file_cmd, new);
			i = i + ft_skip(str+i) + ft_strlen(file_cmd);
			free(file_cmd);
		}
		else if (str[i] == '<' && !flag.s_quote && !flag.d_quote)
		{
			i+=1;
			file_cmd = ft_file(str+i);
			t_file *new = (t_file *)malloc(sizeof(t_file));
			if (!new)
				return ;
			new->file_type = IN;
			ft_lstadd_file(&s->files, file_cmd, new);
			i = i + ft_skip(str+i) + ft_strlen(file_cmd);
			free(file_cmd);
		}
		else if (str[i] == '>' && !flag.s_quote && !flag.d_quote)
		{
			i++;
			file_cmd = ft_file(str+i);
			t_file *new = (t_file *)malloc(sizeof(t_file));
			if (!new)
				return ;
			new->file_type = OUT;
			ft_lstadd_file(&s->files, file_cmd, new);
			i = i + ft_skip(str+i) + ft_strlen(file_cmd);
			free(file_cmd);
		}
		else
		{
			file_cmd = ft_file(str+i);
			size_t k = ft_strlen(file_cmd);
			ft_lstadd_cmd(&s->command, file_cmd);
			i = i + ft_skip(str+i) + k;
			update_quotes(&flag.d_quote, &flag.s_quote, str[i-1]);
			free(file_cmd);
		}
	}
	s->next = NULL;
	if (!data)
		return ;
	if (!(*data))
	{
			*data = s;
			return ;
	}
	d = ft_lstlast_data(*data);
	d->next = s;
}

void    init_data(t_data **data, char **line)
{
	size_t     i;
	size_t  p_nmbr;
	char	**str;

	i = 0;
	p_nmbr = len_double_str(line);
	str = malloc((p_nmbr + 1) * sizeof(char *));
	if (!str)
		return ;
	while (line[i])
	{
		str[i] = ft_strtrim(line[i], "\n\r\v\f\t ");
		i++;
	}
	str[i] = NULL;
	i = 0;
	while (i < p_nmbr)
	{
		full_command(data, str[i]);
		i++; 
	}
  	ft_free(str, p_nmbr);
  }
