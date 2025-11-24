#include <stdio.h>
#define MAX 100

int main() {
    int n, i, j;
    int g[MAX], ex[MAX];
    int gc = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[MAX], arrival[MAX], burst[MAX];
    int completion[MAX], turnaround[MAX], waiting[MAX];
    int is_completed[MAX];

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time of P%d: ", pid[i]);
        scanf("%d", &arrival[i]);
        printf("Enter burst time of P%d: ", pid[i]);
        scanf("%d", &burst[i]);
        is_completed[i] = 0;
    }

    int current_time = 0, completed = 0, min_index;
    int min_burst;

    while (completed != n) {
        min_burst = 1e9;
        min_index = -1;

        for (i = 0; i < n; i++) {
            if (arrival[i] <= current_time && !is_completed[i]) {
                if (burst[i] < min_burst) {
                    min_burst = burst[i];
                    min_index = i;
                } else if (burst[i] == min_burst) {
                    if (arrival[i] < arrival[min_index])
                        min_index = i;
                }
            }
        }

        if (min_index == -1) {
            current_time++;
        } else {
            current_time += burst[min_index];
            completion[min_index] = current_time;
            turnaround[min_index] = completion[min_index] - arrival[min_index];
            waiting[min_index] = turnaround[min_index] - burst[min_index];
            is_completed[min_index] = 1;

            g[gc] = pid[min_index];      // store executed process sequence
	        ex[gc] = current_time;       // store completion time
            gc++;
            completed++;
        }
    }

    // Print Table Header
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               pid[i], arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
    }

    // Calculate and print averages
    float avg_turnaround = 0, avg_waiting = 0;
    for (i = 0; i < n; i++) {
        avg_turnaround += turnaround[i];
        avg_waiting += waiting[i];
    }
    avg_turnaround /= n;
    avg_waiting /= n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround);
    printf("Average Waiting Time: %.2f\n", avg_waiting);

    printf("\nGantt Chart:\n\n");

    // Print process bars
    for (i = 0; i < gc; i++) {
        printf("| P%d ", g[i]);
    }
    printf("|\n");

    // Print timeline
    printf("0");
    for (i = 0; i < gc; i++) {
        printf("    %d", ex[i]);   // spacing for alignment
    }
    printf("\n");

    return 0;
}
