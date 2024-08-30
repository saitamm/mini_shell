/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_final_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:56:08 by lai-elho          #+#    #+#             */
/*   Updated: 2024/08/29 21:35:47 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void free_files(t_file *head) {
    t_file *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->file);  // Free the file name string
        free(tmp);        // Free the node
    }
}
void free_cmds(t_cmd *head) {
    t_cmd *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        
        if (tmp->cmd) {
            printf("Freeing command: %s\n", tmp->cmd);
            free(tmp->cmd);  // Free the command string
        } else {
            printf("Command is NULL\n");
        }
        
        printf("Freeing node\n");
        free(tmp);       // Free the node
    }
}

void free_data(t_data *head) {
    t_data *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        
        // Free the command list
        free_cmds(tmp->command);
        
        // Free the file list
        free_files(tmp->files);
        
        // Free the t_data node
        free(tmp);
    }
}

void print_list(t_env *head)
{
    while (head)
    {
        printf("%s = %s\n", head->key, head->value);
        head = head->next;
    }
}

t_minishell *lstlast_minishell(t_minishell *lst)
{
    if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
int	ft_lstsize(t_cmd *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char    **command_to_array(t_cmd *d)
{
    int     size;
    char    **cmd;
    int     i;

    size = ft_lstsize(d);
    cmd = malloc((size + 1) *sizeof(char *));
    if (!cmd)
        return (NULL);
    i = 0;
    while (d)
    {
        cmd[i] = ft_strdup(d->cmd);
        d = d->next;
        i++;
    }
    cmd[i] = NULL;
    return (cmd);
}
void    to_final_struct(t_data *data, t_minishell **strct)
{
    t_data  *d;
    t_minishell *s;
    t_minishell *k;

    d = data;
    while (d)
    {
        s = malloc(sizeof(t_minishell));
        if (!s)
            return ;
        s->files = NULL;
        s->cmd = command_to_array(d->command);
        s->files = d->files;
        s->next = NULL;
        k = *strct;
        if (!strct)
		    return ;
	    if (!*strct)
	    {
		    *strct = s;
        d = d->next;
		    continue;
	    }
        k = lstlast_minishell(*strct);
	    k->next = s;
        d = d->next;
        // printf(":::::%s\n", d->command->cmd);
    }
}