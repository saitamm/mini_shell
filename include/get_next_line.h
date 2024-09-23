/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:06:38 by lai-elho          #+#    #+#             */
/*   Updated: 2024/01/23 00:25:59 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
#include "./minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

// size_t	ft_strlen(char *c);
// char	*ft_strdup(char *src);
// char	*ft_strjoin(char *s1, char *s2);
int		find_new_line(char *str);
char	*ft_read(int fd, char *str);
char	*get_next_line(int fd);
size_t	ft_len_newline(const char *c);

#endif
