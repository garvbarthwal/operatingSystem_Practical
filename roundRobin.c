#include <stdio.h>

#define MAX 100

int main() {
    int n;
    int g[MAX], ex[MAX];
    int gc = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[MAX], bt[MAX], rt[MAX];
    int ct[MAX], tat[MAX], wt[MAX];
    int queue[MAX], front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        printf("Arrival time of P%d: ", i+1);
        scanf("%d", &at[i]);
        printf("Burst time of P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    int tq;
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    // push all processes that arrive at time 0
    for (int i = 0; i < n; i++)
        if (at[i] == 0)
            queue[rear++] = i;

    // if no one arrived at time 0, jump to earliest arrival
    if (front == rear) {
        int earliest = 0;
        for (int i = 1; i < n; i++)
            if (at[i] < at[earliest])
                earliest = i;
        time = at[earliest];
        queue[rear++] = earliest;
    }

    while (completed < n) {
        int p = queue[front++];   // dequeue

        int exec = (rt[p] > tq) ? tq : rt[p];
        int start = time;
        time += exec;
        rt[p] -= exec;

        g[gc] = p + 1;     // store process ID (1-indexed)
        ex[gc] = time;     // store end time
        gc++;

        // add newly arrived processes during this execution
        for (int i = 0; i < n; i++)
            if (at[i] > start && at[i] <= time && rt[i] > 0)
                queue[rear++] = i;

        if (rt[p] == 0) {
            ct[p] = time;
            completed++;
        } else {
            queue[rear++] = p;  // requeue
        }

        // if queue becomes empty, jump to next arriving process
        if (front == rear && completed < n) {
            int next = -1;
            int minArr = 1e9;
            for (int i = 0; i < n; i++)
                if (rt[i] > 0 && at[i] < minArr) {
                    minArr = at[i];
                    next = i;
                }
            time = at[next];
            queue[rear++] = next;
        }
    }

    float avgTAT = 0, avgWT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgTAT += tat[i];
        avgWT += wt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);
    printf("Average Waiting Time   = %.2f\n", avgWT / n);

    printf("\nGantt Chart:\n");

    // print PIDs with bars
    for (int i = 0; i < gc; i++) {
        printf("| P%d ", g[i]);
    }
    printf("|\n");

    // print time values
    printf("0");
    for (int i = 0; i < gc; i++) {
        printf("   %d", ex[i]);
    }
    printf("\n");
    return 0;
}
