#include <stdio.h>
#include <stdbool.h>

#define MAX 20

typedef struct {
    char name[10];
    int PID;
    int AT; // Arrival Time
    int BT; // Burst Time
    int WT; // Waiting Time
    int TAT; // Turnaround Time
} process;

void getInput(process p[], int *n, int *TQ) {
    printf("Enter the number of processes: ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        p[i].PID = i;
        printf("Enter Process Name: ");
        scanf("%s", p[i].name);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].AT);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].BT);
        p[i].WT = 0;
        p[i].TAT = 0;
    }
    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", TQ);
}

void roundRobin(process p[], int n, int TQ) {
    int rem_BT[MAX];
    for (int i = 0; i < n; i++)
        rem_BT[i] = p[i].BT;

    int time = 0;
    bool done;
    do {
        done = true;
        for (int i = 0; i < n; i++) {
            if (rem_BT[i] > 0) {
                done = false;
                if (rem_BT[i] > TQ) {
                    printf("Process %s executed from time %d to %d\n", p[i].name, time, time + TQ);
                    time += TQ;
                    rem_BT[i] -= TQ;
                } else {
                    printf("Process %s executed from time %d to %d\n", p[i].name, time, time + rem_BT[i]);
                    time += rem_BT[i];
                    rem_BT[i] = 0;
                    p[i].TAT = time - p[i].AT;
                    p[i].WT = p[i].TAT - p[i].BT;
                }
            }
        }
    } while (!done);

    printf("\nProcess\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\n", p[i].name, p[i].WT, p[i].TAT);
    }
}

int main() {
    int n, TQ;
    process p[MAX];
    getInput(p, &n, &TQ);
    printf("\n--- Round Robin Scheduling ---\n");
    roundRobin(p, n, TQ);
    return 0;
}
