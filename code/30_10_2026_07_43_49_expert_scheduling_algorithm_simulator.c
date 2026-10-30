#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the scheduling algorithms as structures
typedef struct {
    int id;
    int arrival_time;
    int burst_time;
} Process;

typedef enum {
    FCFS,
    SJF,
    Priority
} SchedulingAlgorithm;

// Function to calculate the total turnaround time for a given algorithm
double total_turnaround_time(struct Process *processes, int num_processes, SchedulingAlgorithm algorithm) {
    double total_turnaround = 0.0;
    int current_time = 0;
    int finished_processes = 0;

    // Sort processes by arrival time if needed
    qsort(processes, num_processes, sizeof(Process), (int (*)(const void *, const void *))compare_processes);

    for (int i = 0; i < num_processes; i++) {
        while (processes[i].arrival_time > current_time) {
            current_time++;
        }

        if (algorithm == FCFS) {
            total_turnaround += processes[i].burst_time + current_time;
        } else if (algorithm == SJF) {
            int min_burst = INT_MAX;
            for (int j = i; j < num_processes; j++) {
                if (processes[j].arrival_time > current_time && processes[j].burst_time < min_burst) {
                    min_burst = processes[j].burst_time;
                }
            }

            total_turnaround += min_burst + current_time - processes[i].arrival_time;
        } else if (algorithm == Priority) {
            int highest_priority = 0;
            for (int j = i; j < num_processes; j++) {
                if (processes[j].arrival_time > current_time && processes[j].id > highest_priority) {
                    highest_priority = processes[j].id;
                }
            }

            total_turnaround += highest_priority + current_time - processes[i].arrival_time;
        }

        finished_processes++;
    }

    return total_turnaround / finished_processes;
}

// Function to compare two processes based on their arrival time
int compare_processes(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;

    if (p1->arrival_time < p2->arrival_time) return -1;
    else if (p1->arrival_time > p2->arrival_time) return 1;
    else return 0;
}

int main() {
    srand(time(NULL)); // Initialize random seed

    // Generate synthetic data
    int num_processes = 10;
    struct Process processes[num_processes];

    for (int i = 0; i < num_processes; i++) {
        processes[i].id = rand() % 100 + 1;
        processes[i].arrival_time = rand() % 20 + 1;
        processes[i].burst_time = rand() % 10 + 1;
    }

    // Simulate and compare scheduling algorithms
    double fcfs_turnaround = total_turnaround_time(processes, num_processes, FCFS);
    double sjf_turnaround = total_turnaround_time(processes, num_processes, SJF);
    double priority_turnaround = total_turnaround_time(processes, num_processes, Priority);

    printf("FCFS: %.2f\n", fcfs_turnaround);
    printf("SJF: %.2f\n", sjf_turnaround);
    printf("Priority: %.2f\n", priority_turnaround);

    return 0;
}