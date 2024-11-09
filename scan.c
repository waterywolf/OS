#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void scan(int requests[], int n, int initial_head, int max_track) {
    int total_seek_time = 0;
    int current_head = initial_head;

    sort(requests, n);
    total_seek_time += abs(current_head - max_track);
    current_head = max_track;
    printf("Move to right end: %d (Seek Time: %d)\n", max_track, abs(initial_head - max_track));

    for (int i = 0; i < n; i++) {
        if (requests[i] >= initial_head) {
            total_seek_time += abs(current_head - requests[i]);
            current_head = requests[i];
            printf("Move to: %d (Seek Time: %d)\n", current_head, abs(current_head - requests[i]));
        }
    }

    total_seek_time += abs(current_head - 0);
    current_head = 0;
    printf("Move to left end: 0 (Seek Time: %d)\n", abs(current_head));

    for (int i = n - 1; i >= 0; i--) {
        if (requests[i] < initial_head) {
            total_seek_time += abs(current_head - requests[i]);
            current_head = requests[i];
            printf("Move to: %d (Seek Time: %d)\n", current_head, abs(current_head - requests[i]));
        }
    }

    printf("Total Seek Time: %d\n", total_seek_time);
}

int main() {
    int requests[MAX_REQUESTS];
    int n, initial_head, max_track;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    printf("Enter the maximum track number: ");
    scanf("%d", &max_track);

    printf("\n--- SCAN (Elevator Algorithm) ---\n");
    scan(requests, n, initial_head, max_track);

    return 0;
}
