#include <stdio.h>     
#include <stdlib.h>     
#include <unistd.h>     
#include <string.h>     
#include <sys/types.h>  
#include <sys/wait.h>   

int main()
{
    int pipefd[2];
    pid_t pid;
    char write_message[] = "Hello from Parent Process!";
    char read_message[100];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        printf("Parent Process: Sending message to child...\n");

        close(pipefd[0]);

        write(pipefd[1], write_message, strlen(write_message) + 1);
        printf("Parent Process: Message sent successfully.\n");

        close(pipefd[1]);

        wait(NULL);
        printf("Parent Process: Child process completed.\n");
    }
    else
    {
        close(pipefd[1]);

        read(pipefd[0], read_message, sizeof(read_message));
        printf("Child Process: Message received: %s\n", read_message);

        close(pipefd[0]);
        exit(0);
    }

    return 0;
}
