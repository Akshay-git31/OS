#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main()
{
    int shmid;
    pid_t pid;
    char *shared_memory;
    char message[] = "Hello from Parent Process!";

    shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory created successfully.\n");

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)-1)
        {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        printf("Parent Process: Writing message to shared memory...\n");
        strcpy(shared_memory, message);
        printf("Parent Process: Message written successfully.\n");

        shmdt(shared_memory);
        wait(NULL);

        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }
        printf("Parent Process: Shared memory removed.\n");
    }
    else
    {
        sleep(1);
        shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)-1)
        {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        printf("Child Process: Reading message from shared memory...\n");
        printf("Child Process: Message received: %s\n", shared_memory);

        shmdt(shared_memory);
    }

    return 0;
}
