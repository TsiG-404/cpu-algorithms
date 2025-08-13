#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid; // process ID
	int at; // arrival time
	int bt; // burst time
} process;


void fcfs(int n, process *processes) {
    // Sortting
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].at > processes[j + 1].at) {
                // Swapping
                process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

  

    // Print
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].bt; j++) {
            printf("%d\n", processes[i].pid);
        }
    }
    
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
    
    fcfs(n, arr);

    // free memory
    free(arr);

    return 0;/* DO NOT EDIT THIS LINE */
}
//Kostantinos Tsigkas 3923