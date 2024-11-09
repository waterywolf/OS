#include <stdio.h>

int n, nf;
int in[100];
int p[50];
int pgfaultcnt = 0;

void getData() {
    printf("\nEnter the length of the page reference sequence: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);
    printf("Enter the number of frames: ");
    scanf("%d", &nf);
}

void initialize() {
    pgfaultcnt = 0;
    for (int i = 0; i < nf; i++)
        p[i] = -1;
}

int isHit(int data) {
    for (int j = 0; j < nf; j++) {
        if (p[j] == data) {
            return 1;
        }
    }
    return 0;
}

void dispPages() {
    printf(" | Frames: ");
    for (int k = 0; k < nf; k++) {
        if (p[k] != -1)
            printf(" %d ", p[k]);
        else
            printf(" - ");
    }
    printf("\n");
}

void dispPgFaultCnt() {
    printf("\nTotal number of page faults: %d\n", pgfaultcnt);
}

void fifo() {
    initialize();
    int pointer = 0;

    for (int i = 0; i < n; i++) {
        printf("\nProcessing page %d", in[i]);

        if (!isHit(in[i])) {
            p[pointer] = in[i];
            pointer = (pointer + 1) % nf;
            pgfaultcnt++;
            printf(" | Page fault occurred. ");
            dispPages();
        } else {
            printf(" | No page fault.");
            dispPages();
        }
    }
    dispPgFaultCnt();
}

int main() {
    getData();
    printf("\n--- FIFO Page Replacement ---\n");
    fifo();
    return 0;
}
