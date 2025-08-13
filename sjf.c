#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid; // process ID
    int at;  // arrival time
    int bt;  // burst time
} process;

// Structure to represent a node in the priority queue
typedef struct Node {
    process data;
    struct Node* next;
} Node;

// Priority queue functions
Node* push(Node* head, process data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if (head == NULL || data.bt < head->data.bt) {
        new_node->next = head;
        return new_node;
    }

    Node* current = head;
    while (current->next != NULL && data.bt >= current->next->data.bt) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;

    return head;
}

Node* pop(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* temp = head;
    head = head->next;
    free(temp);

    return head;
}

int any_process_remaining(process* processes, int n) {
    for (int i = 0; i < n; i++) {
        if (processes[i].bt > 0) {
            return 1;
        }
    }
    return 0;
}

void sjf(int n, process* processes) {
    Node* priority_queue = NULL;
    int current_time = 0;

    

    while (any_process_remaining(processes, n)) {
        // Push processes that have arrived into the priority queue
        for (int i = 0; i < n; i++) {
            if (processes[i].at == current_time && processes[i].bt > 0) {
                priority_queue = push(priority_queue, processes[i]);
            }
        }

        if (priority_queue != NULL) {
            // Pop the process with the shortest burst time
            process current_process = priority_queue->data;
            priority_queue = pop(priority_queue);

            // Print the process ID for each unit of time in its burst time
            for (int t = 0; t < current_process.bt; t++) {
                printf("%d\n",current_process.pid);
            }

            // Update current time and burst time for the completed process
            current_time += current_process.bt;
            current_process.bt = 0;

            // Update the processes array
            processes[current_process.pid - 1] = current_process;
        } else {
            // Increment current time if no process is ready to run
            current_time++;
        }
    }

    // Free memory allocated for the priority queue
    while (priority_queue != NULL) {
        priority_queue = pop(priority_queue);
    }
}

// Function to compare processes based on arrival time
int compareArrivalTime(const void* a, const void* b) {
    return ((process*)a)->at - ((process*)b)->at;
}

int main() {
    int n;
    int quantum;
    scanf("%d", &n);
    scanf("%d", &quantum);
    process* arr;
    arr = malloc(n * sizeof(process));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i].pid);
        scanf("%d", &arr[i].at);
        scanf("%d", &arr[i].bt);
    }

    // Sort processes based on arrival time
    qsort(arr, n, sizeof(process), compareArrivalTime);

    sjf(n, arr);

    // Free memory
    free(arr);

    return 404;
}
