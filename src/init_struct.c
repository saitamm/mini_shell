/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:59:21 by sait-amm          #+#    #+#             */
/*   Updated: 2024/08/31 20:50:18 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
int	append_her_doc(char a, char b)
{
	if (a == '<' && a == b)
		return (1);
	else if (a == '>' && a == b)
		return (1);
	return (0);
}

// void	add_node_file(t_file **s, char *str)
// {
// 	char	*file_name;
	
	
// }
void	full_command(t_data **data, char *str)
{
	int		i;
	t_flag	flag;
	t_data *s;
	t_data	*d;
	char	*file_cmd;

	
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
		update_quotes(&flag.d_quote, &flag.s_quote, str[i]);
		if (append_her_doc(str[i], str[i+1]) && !flag.s_quote && !flag.d_quote)
		{
			i = i+2;
			// add_node_file(&s, str + i);
			t_file *new = (t_file *)malloc(sizeof(t_file));
			if (!new)
				return ;
			file_cmd = ft_file(str+i);
			if (str[i - 1] == '<')
			{
				// printf("her_doc +== *%c*\n", str[i]);
				new->file_type = HER_DOC;
			}
			else
			{
				// printf(">>>>>append == *%c*\n", str[i]);
				new->file_type = APPEND;
			}
			ft_lstadd_file(&s->files, file_cmd, new);
			i = i + ft_skip(str+i) + ft_strlen(file_cmd);
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
		}
		else if (str[i] == '>' && !flag.s_quote && !flag.d_quote)
		{
			file_cmd = ft_file(str+i);
			i+=1;
			t_file *new = (t_file *)malloc(sizeof(t_file));
			if (!new)
				return ;
			new->file_type = OUT;
			ft_lstadd_file(&s->files, file_cmd, new);
			i = i + ft_skip(str+i) + ft_strlen(file_cmd);
		}
		else
		{
			file_cmd = ft_file(str+i);
			size_t k = ft_strlen(file_cmd);
			ft_lstadd_cmd(&s->command, file_cmd);
			i = i + ft_skip(str+i) + k;		
			update_quotes(&flag.d_quote, &flag.s_quote, str[i-1]);
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

// void ft_skip_whitespace(int *i, char *str) {
//     while (ft_whitespace(str[*i])) (*i)++;
// }

// void ft_update_quotes(t_flag *flag, char c) {
//     update_quotes(&flag->d_quote, &flag->s_quote, c);
// }

// int is_redirection(char c, char next_c) {
//     return (c == '<' || c == '>') && next_c == c;
// }

// t_file *create_file_node(int *i, char *str) {
//     (*i) += 2;
//     t_file *new = (t_file *)malloc(sizeof(t_file));
//     if (!new) return NULL;
//     new->file = ft_file(str + (*i));
//     new->file_type = (str[*i] == '<') ? HER_DOC : APPEND;
//     *i += ft_skip(str + (*i)) + ft_strlen(new->file);
//     return new;
// }

// void add_data_node(t_data **data, t_data *s) {
//     s->next = NULL;
//     if (!(*data)) {
//         *data = s;
//     } else {
//         t_data *last = ft_lstlast_data(*data);
//         last->next = s;
//     }
// }

// void full_command(t_data **data, char *str) {
//     int i = 0;
//     t_flag flag = {false, false};
//     t_data *s = (t_data *)malloc(sizeof(t_data));
// 	char *file_cmd;
//     if (!s) return;
//     s->files = NULL;
//     s->command = NULL;

//     while (str[i]) {
//         ft_skip_whitespace(&i, str);
//         ft_update_quotes(&flag, str[i]);

//         if (is_redirection(str[i], str[i + 1]) && !flag.s_quote && !flag.d_quote) {
//             t_file *new_file = create_file_node(&i, str);
//             if (!new_file) return;
//             ft_lstadd_file(&s->files, new_file->file, new_file);
//         } else if (!flag.s_quote && !flag.d_quote) {
//             file_cmd = ft_file(str + i);
//             ft_lstadd_cmd(&s->command, file_cmd);
//             i += ft_skip(str + i) + ft_strlen(file_cmd);
//             ft_update_quotes(&flag, str[i - 1]);
//         }
//     }

//     add_data_node(data, s);
// }



void    init_data(t_data **data, char **line)
{
	size_t     i;
	size_t  p_nmbr;

	i = -1;
	while (line[++i])
		line[i] = ft_strtrim(line[i], "\n\r\v\f\t ");
	i = 0;
	p_nmbr = len_double_str(line);
	while (i < p_nmbr)
	{
		full_command(data, line[i]);
		i++; 
	}
}
