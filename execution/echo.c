#include "../include/minishell.h"

void ft_find_in_env(char *search_key) {
    while (g_global->env != NULL) {
        if (strcmp(g_global->env->key, search_key) == 0) {
            printf("%s\n", g_global->env->value);
            return;
        }
        g_global->env = g_global->env->next;
    }
    printf("Key not found: %s\n", search_key);
}


int check_n(const char *s) {
    int i = 1; 
    while (s[i] == 'n') {
        i++;
    }
        if (s[i] == '\0') 
            return 1;
        else
        return 0;
    }

void    ft_echo(char **str) {
    int j = 1;
    int newline = 1;

    while (str[j] && str[j][0] == '-' && check_n(str[j])) {
        newline = 0;
        j++;
    }
    while (str[j])
    {
        int i = 0;
        while (str[j][i])
        {
            if (str[j][i] == '$' && str[j][i + 1] == '?')
            {
                printf("%d", g_global->exit_status);
                break;
            } 
            else
                write(1, &str[j][i], 1);
            i++;
        }
        if (str[j + 1]) {
            write(1, " ", 1);
        }
        j++;
    }
    if (newline)
        write(1, "\n", 1);
}