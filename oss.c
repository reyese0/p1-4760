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

    //Parse command line arguments
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

    return 0;
}