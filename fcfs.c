#include<stdio.h>
#define MAX 100

int main(){
    int n,pid[MAX],arrival[MAX],burst[MAX],completion[MAX],turnaround[MAX],waiting[MAX];

    printf("Enter number of processes :");
    scanf("%d",&n);
    
    printf("\nEnter Arrival Time for %d processes\n",n);
    for(int i=0;i<n;i++){
        pid[i]=i+1;
        scanf("%d",&arrival[i]);
    }

    printf("\nEnter Burst Time for %d processes\n",n);
    for(int i=0;i<n;i++){
        scanf("%d",&burst[i]);
    }

    //sort by arrival time 

    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            int temp;
            if(arrival[j]>arrival[j+1]){

                temp=arrival[j];
                arrival[j]=arrival[j+1];
                arrival[j+1]=temp;

                temp=burst[j];
                burst[j]=burst[j+1];
                burst[j+1]=temp;

                temp=pid[j];
                pid[j]=pid[j+1];
                pid[j+1]=temp;

            }
        }
    }

    //calculate completion time 
    completion[0]=arrival[0]+burst[0];
    for(int i=1;i<n;i++){
        if(arrival[i]>completion[i-1]){
            completion[i]=arrival[i]+burst[i];
        } else {
            completion[i]=completion[i-1]+burst[i];
        }
    }

    //calculate turnaround and waiting time
    for(int i=0;i<n;i++){
        turnaround[i]=completion[i] - arrival[i];
        waiting[i]=turnaround[i] - burst[i];
    }

    printf("P\tArrival\tBurst\tCompletion\tTurnaround\tWaitng\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t\t%d\t%d\t\t%d\n",pid[i],arrival[i],burst[i],completion[i],turnaround[i],waiting[i]);
    }

    //calculate average tat,waiting
    float avg_tat=0.0,avg_waiting=0.0;
    int total_tat=0,total_waiting=0.0;
    for(int i=0;i<n;i++){
        total_tat+=turnaround[i];
        total_waiting+=waiting[i];
    }

    avg_tat = (float) total_tat / n;
    avg_waiting = (float) total_waiting / n;

    printf("\nAvg TAT: %.2f\tAvg Waiting: %.2f\n", avg_tat, avg_waiting);

    printf("\nGantt Chart:\n\n");

// Print process bars
for (int i = 0; i < n; i++) {
    printf("| P%d ", pid[i]);
}
printf("|\n");

// Print timeline
printf("0");
for (int i = 0; i < n; i++) {
    printf("    %d", completion[i]);   // spaces for alignment
}
printf("\n");
    return 0;
}