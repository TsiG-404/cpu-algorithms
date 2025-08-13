#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid; // process ID
    int at; // arrival time
    int bt; // burst time
} process;

// Function to perform Round Robin scheduling
void roundRobin(int n, process *processes, int quantum) {
    int currentTime = 0;
    int *remainingTime = (int *)malloc(n * sizeof(int));
    int *completionTime = (int *)malloc(n * sizeof(int));
    int completedProcesses = 0;

    // Initialize remaining time and completion time arrays
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].bt;
        completionTime[i] = -1;
    }

    // Execute processes in a round-robin fashion
    while (completedProcesses < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && remainingTime[i] > 0) {
                int executionTime = (remainingTime[i] < quantum) ? remainingTime[i] : quantum;

                for (int j = 0; j < executionTime; j++) {
                    printf("%d\n", processes[i].pid);
                    currentTime++;
                }

                remainingTime[i] -= executionTime;

                if (remainingTime[i] == 0 && completionTime[i] == -1) {
                    completionTime[i] = currentTime;
                    completedProcesses++;
                }
            }
        }
    }

    

   
    


    // Free allocated memory
    free(remainingTime);
    free(completionTime);
}

int main() {
    /* read in data - DO NOT EDIT (START) */
	int n;
	int quantum;
	scanf("%d", &n);
	scanf("%d", &quantum);
	process *arr;
	arr = malloc(n * sizeof(process));
	for (int i = 0; i < n ; ++i) {
		scanf("%d", &arr[i].pid);
		scanf("%d", &arr[i].at);
		scanf("%d", &arr[i].bt);
	}
	/* read in data - DO NOT EDIT (END) */
    
    roundRobin(n, arr, quantum);

    // Free allocated memory
    free(arr);

    return 0;
}
