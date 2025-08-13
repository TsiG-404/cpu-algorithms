#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int at;
    int bt;
} process;

void srtf(process *processes[], int n) {
    int total_burst_time = 0;
    for (int i = 0; i < n; i++) {
        total_burst_time += processes[i]->bt;
    }

    int current_time = 0;

    while (current_time < total_burst_time) {
        int runnable_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i]->at <= current_time && processes[i]->bt > 0) {
                if (runnable_index == -1 || processes[i]->bt < processes[runnable_index]->bt) {
                    runnable_index = i;
                }
            }
        }

        if (runnable_index == -1) {
            current_time++;
            continue;
        }

        process *running_process = processes[runnable_index];
        printf("%d\n", running_process->pid);
        running_process->bt--;
        current_time++;
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

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i].pid);
        scanf("%d", &arr[i].at);
        scanf("%d", &arr[i].bt);
    }
    
    /* read in data - DO NOT EDIT (END) */

    // Convert the array of structures to an array of pointers
    process **arr_of_pointers = malloc(n * sizeof(process *));
    for (int i = 0; i < n; i++) {
        arr_of_pointers[i] = &arr[i];
    }

    srtf(arr_of_pointers, n);

    free(arr);  // Free allocated memory
    free(arr_of_pointers);  // Free the array of pointers

    return 0;
}
