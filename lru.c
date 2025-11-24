#include <stdio.h>

int main() {
    int pages[100], frames[10], lastUsed[10];
    int n, f, i, j, faults = 0, hits = 0, time = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (i = 0; i < f; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    for (i = 0; i < n; i++) {
        int page = pages[i];
        time++;
        int hit = 0;

        // Check for hit
        for (j = 0; j < f; j++) {
            if (frames[j] == page) {
                hit = 1;
                hits++;
                lastUsed[j] = time; // update usage time
                break;
            }
        }

        if (!hit) {
            faults++;

            // Try to find empty frame first
            int pos = -1;
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, find LRU frame
            if (pos == -1) {
                pos = 0;
                for (j = 1; j < f; j++) {
                    if (lastUsed[j] < lastUsed[pos])
                        pos = j;
                }
            }

            frames[pos] = page;
            lastUsed[pos] = time;
        }

        // Print frame state
        printf("After ref %2d (page %d): ", i + 1, page);
        for (j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    float hit_ratio = (float)hits / n;

    printf("\nTotal Page Faults = %d\n", faults);
    printf("Total Page Hits   = %d\n", hits);
    printf("Hit Ratio         = %.2f\n", hit_ratio);

    return 0;
}