#include <stdio.h>

int main()
{
    int block[20], process[20];
    int allocation[20];
    int tempBlock[20];
    int m, n, choice;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter sizes of memory blocks:\n");
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &block[i]);
        tempBlock[i] = block[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter sizes of processes:\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &process[i]);
        allocation[i] = -1;
    }

    printf("\nMemory Allocation Techniques");
    printf("\n1. First Fit");
    printf("\n2. Best Fit");
    printf("\n3. Worst Fit");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        // FIRST FIT
        case 1:
        {
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(tempBlock[j] >= process[i])
                    {
                        allocation[i] = j;
                        tempBlock[j] -= process[i];
                        break;
                    }
                }
            }

            printf("\n----- First Fit Allocation -----\n");
            break;
        }

        // BEST FIT
        case 2:
        {
            for(int i = 0; i < n; i++)
            {
                int bestIndex = -1;

                for(int j = 0; j < m; j++)
                {
                    if(tempBlock[j] >= process[i])
                    {
                        if(bestIndex == -1 ||
                           tempBlock[j] < tempBlock[bestIndex])
                        {
                            bestIndex = j;
                        }
                    }
                }

                if(bestIndex != -1)
                {
                    allocation[i] = bestIndex;
                    tempBlock[bestIndex] -= process[i];
                }
            }

            printf("\n----- Best Fit Allocation -----\n");
            break;
        }

        // WORST FIT
        case 3:
        {
            for(int i = 0; i < n; i++)
            {
                int worstIndex = -1;

                for(int j = 0; j < m; j++)
                {
                    if(tempBlock[j] >= process[i])
                    {
                        if(worstIndex == -1 ||
                           tempBlock[j] > tempBlock[worstIndex])
                        {
                            worstIndex = j;
                        }
                    }
                }

                if(worstIndex != -1)
                {
                    allocation[i] = worstIndex;
                    tempBlock[worstIndex] -= process[i];
                }
            }

            printf("\n----- Worst Fit Allocation -----\n");
            break;
        }

        default:
            printf("Invalid Choice!\n");
            return 0;
    }

    // Tabular Output
    printf("\n");
    printf("-------------------------------------------------------------\n");
    printf("Process\tProcess Size\tAllocated Block\tRemaining Block Size\n");
    printf("-------------------------------------------------------------\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t",
               i + 1, process[i]);

        if(allocation[i] != -1)
        {
            printf("%d\t\t%d\n",
                   allocation[i] + 1,
                   tempBlock[allocation[i]]);
        }
        else
        {
            printf("Not Allocated\t-\n");
        }
    }

    printf("-------------------------------------------------------------\n");

    return 0;
}
