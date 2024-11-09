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

void lru() {
    initialize();
    int least[50];

    for (int i = 0; i < n; i++) {
        printf("\nProcessing page %d", in[i]);

        if (!isHit(in[i])) {
            for (int j = 0; j < nf; j++) {
                int pg = p[j];
                int found = 0;

                for (int k = i - 1; k >= 0; k--) {
                    if (pg == in[k]) {
                        least[j] = k;
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    least[j] = -1;
            }

            int min = 9999, repindex = 0;
            for (int j = 0; j < nf; j++) {
                if (least[j] < min) {
                    min = least[j];
                    repindex = j;
                }
            }

            p[repindex] = in[i];
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
    printf("\n--- LRU Page Replacement ---\n");
    lru();
    return 0;
}
