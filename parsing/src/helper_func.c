/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:10:35 by sait-amm          #+#    #+#             */
/*   Updated: 2024/10/06 10:13:53 by sait-amm         ###   ########.fr       */
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

int	ft_skip(char *str)
{
	int	i;

	i = 0;
	while (ft_whitespace(str[i]) && str[i])
		i++;
	return (i);
}

t_minishell	*lstlast_minishell(t_minishell *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
