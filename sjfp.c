#include <stdio.h>
#include <limits.h>
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

void getInput(process p[], int *n) {
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
}

void sjfPreemptive(process p[], int n) {
    int rem_BT[MAX];
    for (int i = 0; i < n; i++)
        rem_BT[i] = p[i].BT;

    int complete = 0, time = 0, min_index;
    bool found;

    while (complete < n) {
        min_index = -1;
        int min_BT = INT_MAX;
        found = false;

        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && rem_BT[i] > 0 && rem_BT[i] < min_BT) {
                min_BT = rem_BT[i];
                min_index = i;
                found = true;
            }
        }

        if (!found) {
            time++;
            continue;
        }

        rem_BT[min_index]--;
        time++;

        if (rem_BT[min_index] == 0) {
            complete++;
            p[min_index].TAT = time - p[min_index].AT;
            p[min_index].WT = p[min_index].TAT - p[min_index].BT;
        }
    }

    printf("\nProcess\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\n", p[i].name, p[i].WT, p[i].TAT);
    }
}

int main() {
    int n;
    process p[MAX];
    getInput(p, &n);
    printf("\n--- Shortest Job First Preemptive Scheduling ---\n");
    sjfPreemptive(p, n);
    return 0;
}
