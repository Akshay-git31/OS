#include <stdio.h>

int main()
{
    int pages[50], frames[10];
    int n, f;
    int i, j;
    int pageFaults = 0, pageHits = 0;
    int found, pos;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            pageHits++;
        }
        else
        {
            pageFaults++;
            pos = -1;

            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
            {
                int k, lastUsed, leastRecent = i;
                for (j = 0; j < f; j++)
                {
                    lastUsed = -1;
                    for (k = i - 1; k >= 0; k--)
                    {
                        if (pages[k] == frames[j])
                        {
                            lastUsed = k;
                            break;
                        }
                    }
                    if (lastUsed < leastRecent)
                    {
                        leastRecent = lastUsed;
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
        }

        printf("%d\t", pages[i]);
        for (j = 0; j < f; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found)
            printf("\tHit");
        else
            printf("\tPage Fault");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits = %d\n", pageHits);

    return 0;
}
