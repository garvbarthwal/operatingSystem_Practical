#include <stdio.h>

int main() {
    int pages[100], frames[10];
    int n, f, i, j, faults = 0, hits = 0;
    int front = 0;  // FIFO pointer

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (i = 0; i < f; i++)
        frames[i] = -1;

    for (i = 0; i < n; i++) {
        int page = pages[i];
        int hit = 0;

        // Check for hit
        for (j = 0; j < f; j++) {
            if (frames[j] == page) {
                hit = 1;
                hits++;
                break;
            }
        }

        // If miss → page fault
        if (!hit) {
            faults++;

            // Place page at FIFO position
            frames[front] = page;

            // Move FIFO pointer forward
            front = (front + 1) % f;
        }

        // Print current frames
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
