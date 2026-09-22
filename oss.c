//Elisa Reyes
//9/20/2026

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void print_help() {
    printf("How to use: oss [-h] [-n proc] [-s simul] [-t iter]\n");
    printf("  -h Show help message\n");
    printf("  -n proc Total number of children to launch\n");
    printf("  -s simul Maximum number of children to run simultaneously\n");
    printf("  -t iter Number of iterations to pass to the user process\n");
}

int main(int argc, char* argv[]) { 
    const char optstr[] = "hn:s:t:";
    char opt;
    pid_t pid;
    int maxProcesses = 0;
    int maxSimul = 0;
    int iterations = 0;
    int currentProcesses = 0;
    int totalProcesses = 0;

    while ((opt = getopt(argc, argv, optstr)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 'n':
                maxProcesses = atoi(optarg);
                break;
            case 's':
                maxSimul = atoi(optarg);
                break;
            case 't':
                iterations = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Invalid option\n");
                print_help();
                return 1;
        }
    }

    printf("OSS: Launching %d children, %d simultaneous, with %d iterations\n",
           maxProcesses, maxSimul, iterations);

    while (currentProcesses < maxSimul) {
        if (totalProcesses >= maxProcesses) {
            break; // Exit if total processes reached
        }

        pid = fork(); // Create new process

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char strArg[20]; 
            sprintf(strArg, "%d", iterations); //Convert iterations to string and pass it as an argument to the user
            char* args[] = {"./user", strArg, NULL}; //Arguments to pass to the user process
            execvp(args[0], args); 

            perror("execl failed");
            exit(EXIT_FAILURE);
        } 
        
        printf("OSS: Created child with PID %d\n", pid);
        currentProcesses++;
        totalProcesses++;
    }

    while (totalProcesses < maxProcesses) {
        //Wait for a child process to finish before creating a new one
        if (wait(0) > 0) { 
            currentProcesses--; //Decrease count of current processes if a child process finishes
        }

        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { 
            char strArg[20];
            sprintf(strArg, "%d", iterations);
            char* args[] = {"./user", strArg, NULL}; 
            execvp(args[0], args); 

            perror("execl failed");
            exit(EXIT_FAILURE);
        }
        
        currentProcesses++;
        totalProcesses++;
    }

    //Wait for all child processes to finish
    while (currentProcesses > 0) { 
        if (wait(0) > 0) {
            currentProcesses--;
        }
    }
    
    printf("OSS: Summary - Total processes finished %d\n", totalProcesses);

    return 0;
}