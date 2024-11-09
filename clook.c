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

void clook(int requests[], int n, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;
    sort(requests, n);

    int initial_index = 0;
    while (initial_index < n && requests[initial_index] <= initial_head) {
        initial_index++;
    }

    for (int i = initial_index; i < n; i++) {
        int seek = abs(current_head - requests[i]);
        total_seek_time += seek;
        printf("Move from %d to %d (Seek Time: %d)\n", current_head, requests[i], seek);
        current_head = requests[i];
    }

    if (initial_index > 0) {
        total_seek_time += abs(current_head - requests[0]);
        printf("Move from %d to %d (Seek Time: %d)\n", current_head, requests[0], abs(current_head - requests[0]));
        current_head = requests[0];
    }

    for (int i = 1; i < initial_index; i++) {
        int seek = abs(current_head - requests[i]);
        total_seek_time += seek;
        printf("Move from %d to %d (Seek Time: %d)\n", current_head, requests[i], seek);
        current_head = requests[i];
    }

    printf("Total Seek Time: %d\n", total_seek_time);
}

int main() {
    int requests[MAX_REQUESTS];
    int n, initial_head;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    printf("\n--- C-LOOK (Circular LOOK Algorithm) ---\n");
    clook(requests, n, initial_head);

    return 0;
}
