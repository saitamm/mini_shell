/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:56:40 by lai-elho          #+#    #+#             */
/*   Updated: 2024/08/30 13:28:01 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct s_execution
{
    int ac;
    char **av;
    char  **env;
}              t_execution;


typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;


void ft_echo(int ac, char **str, char **env);
void parse_env_var(char **env_var);

void ft_pwd(void);
void ft_cd(char *path);
void print_env(t_env *head);
char	*ft_strchr(const char *str, int c);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *c);
char *ft_strcpy(char *dest, const char *src);
char    *find_home_path();
void	unset(char **av);
// void ft_builtins(char *buff);
void	unset(char **av);

#endif