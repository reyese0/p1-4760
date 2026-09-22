//Elisa Reyes
//9/20/2026

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) { 
    int iter = atoi(argv[1]); // Convert the first command line argument to an integer  
    
    for (int i = 1; i <= iter; i++) { 
        pid_t pid = getpid(); // Get process ID
        pid_t ppid = getppid(); // Get parent process ID

        printf("USER PID:%d PPID:%d Iteration:%d before sleeping\n", pid, ppid, i);
        sleep(1); 
        printf("USER PID:%d PPID:%d Iteration:%d after sleeping\n", pid, ppid, i);
    }

    return 0;
}