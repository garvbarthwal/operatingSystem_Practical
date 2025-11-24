#include <stdio.h>

int main() {
    int pages[100], frames[10];
    int n, f, i, j, k, faults = 0, hits = 0;

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

            int pos = -1;

            // Check for empty frame first
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame → find optimal victim
            if (pos == -1) {
                int farthest = -1;
                pos = 0;

                for (j = 0; j < f; j++) {
                    int nextUse = -1;

                    // Find when this frame's page is next used
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }

                    // If never used in future → replace immediately
                    if (nextUse == -1) {
                        pos = j;
                        break;
                    }

                    // Choose the page used farthest in the future
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        pos = j;
                    }
                }
            }

            frames[pos] = page;
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
