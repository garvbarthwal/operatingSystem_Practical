#include <stdio.h>
#define MAX 100

int main() {
    int n, i;
    int g[MAX], ex[MAX];
    int gc = 0;
    int completed = 0, current_time = 0, min_remaining, min_index;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[MAX], arrival[MAX], burst[MAX], remaining[MAX];
    int completion[MAX], turnaround[MAX], waiting[MAX];
    int is_completed[MAX];

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time of P%d: ", pid[i]);
        scanf("%d", &arrival[i]);
        printf("Enter burst time of P%d: ", pid[i]);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
        is_completed[i] = 0;
    }

    while (completed != n) {
        min_remaining = 1e9;
        min_index = -1;

        for (i = 0; i < n; i++) {
            if (arrival[i] <= current_time && !is_completed[i] && remaining[i] < min_remaining && remaining[i] > 0) {
                min_remaining = remaining[i];
                min_index = i;
            }
        }

        if (min_index == -1) {  // CPU idle
            current_time++;
        } else {
            // Execute process for 1 unit
            g[gc] = pid[min_index];
            remaining[min_index]--;
            current_time++;
            ex[gc] = current_time;    // store time
            gc++;
            if (remaining[min_index] == 0) {
                completion[min_index] = current_time;
                turnaround[min_index] = completion[min_index] - arrival[min_index];
                waiting[min_index] = turnaround[min_index] - burst[min_index];
                is_completed[min_index] = 1;
                completed++;
            }
        }
    }

    // Print Table header
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

    printf("\nGantt Chart:\n");

    // process execution (with bars)
    for (i = 0; i < gc; i++) {
        printf("| P%d ", g[i]);
    }
    printf("|\n");

    // time values
    printf("0");
    for (i = 0; i < gc; i++) {
        printf("   %d", ex[i]);
    }
    printf("\n");
    return 0;
}