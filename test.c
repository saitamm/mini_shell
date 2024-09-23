
#include "include/minishell.h"

int main()
{
    int save_fd = dup(STDIN_FILENO);
    int pipe_fd[2];
    pipe(pipe_fd);
    int pid1 = fork();
    if (pid1 == 0)
    {
        close(pipe_fd[0]);
        char *arg[] = {"/bin/cat","Makefile", NULL};
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        execve("/bin/cat", arg, NULL);
        exit(1);
    }
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    int pid2 = fork();
    if(pid2 == 0)
    {
        char *arg[] = { "/bin/grep" , "x" , NULL};
        execve("/bin/grep", arg, NULL);
        exit(1);
    }
    dup2(save_fd, STDIN_FILENO); 
    close(pipe_fd[0]);
} 