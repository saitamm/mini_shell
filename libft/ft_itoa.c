/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:32:40 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/23 09:34:19 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdlib.h>

static int ft_intlen(int n) {
    int len ;

    if (n < 0)
        len = 1;
    else
        len = 0;
    while (n != 0) {
        len++;
        n /= 10;
    }
    return len;
}

char *ft_itoa(int n)
{
    int len;
    char *str;
    long num;
    
    len = ft_intlen(n);
    str = (char *)malloc(sizeof(char) * (len + 1));
    num = n;
    if (!str)
        return NULL;
    str[len] = '\0';
    if (num < 0) {
        str[0] = '-';
        num = -num;
    }
    if (num == 0)
        str[0] = '0';
    while (num > 0) {
        str[--len] = (num % 10) + '0';
        num /= 10;
    }
    return str;
}
