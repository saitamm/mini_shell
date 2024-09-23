/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:52:20 by lai-elho          #+#    #+#             */
/*   Updated: 2024/09/17 21:14:01 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <sys/wait.h>

void execute_pipeline(char *cmd1[], char *cmd2[]) {
    int pipefd[2]; // Pipe file descriptors
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(0);
    }

    // Fork the first process
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(0);
    }

    if (pid1 == 0) {
        // In the first child process
        // Close the read end of the pipe
        close(pipefd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // Execute the first command
        if (execvp(cmd1[0], cmd1) == -1) {
            perror("execvp");
            exit(0);
        }
    }

    // Fork the second process
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(0);
    }

    if (pid2 == 0) {
        // In the second child process
        // Close the write end of the pipe
        close(pipefd[1]);

        // Redirect stdin to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // Execute the second command
        if (execvp(cmd2[0], cmd2) == -1) {
            perror("execvp");
            exit(0);
        }
    }

    // In the parent process
    // Close both ends of the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

// int main() {
//     // Example commands: ls | grep c
//     char *cmd1[] = {"ls", NULL};
//     char *cmd2[] = {"grep", "c", NULL};

//     execute_pipeline(cmd1, cmd2);

//     return 0;
// }
