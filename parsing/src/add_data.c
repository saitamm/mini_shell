/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:36:48 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/07 12:19:11 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data	*ft_lstlast_data(t_data *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	full_command(t_data **data, char *str)
{
	int		i;
	t_flag	flag;
	t_data	*s;

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
		if ((str[i] == '<' || str[i] == '>') && !flag.s_quote && !flag.d_quote)
			add_file(&i, str, &s);
		else
			add_cmd(&i, &s, str);
	}
	s->next = NULL;
	data = add_data(data, s);
}

void	init_data(t_data **data, char **line)
{
	size_t	i;
	size_t	p_nmbr;
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

t_data	**add_data(t_data **data, t_data *new)
{
	t_data	*d;

	if (!data)
		return (NULL);
	if (!(*data))
	{
		*data = new;
		return (NULL);
	}
	d = ft_lstlast_data(*data);
	d->next = new;
	return (data);
}
