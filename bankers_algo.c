#include <stdio.h>
#define MAX 10
int main() {
    int n, m, i, j;
    int alloc[MAX][MAX], need[MAX][MAX], avail[MAX];
    int finish[MAX] = {0}, seq[MAX], count = 0;
    printf("Enter number of processes: ");    scanf("%d", &n);
    printf("Enter number of resource types: "); scanf("%d", &m);
    printf("\nEnter Allocation matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    printf("\nEnter Max matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++) {
            int max; scanf("%d", &max);
            need[i][j] = max - alloc[i][j];
        }
    printf("\nEnter Available resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);
    while(count < n) {
        int found = 0;
        for(i = 0; i < n; i++) {
            if(finish[i]) continue;
            for(j = 0; j < m && need[i][j] <= avail[j]; j++);
            if(j == m) {
                for(j = 0; j < m; j++)
                    avail[j] += alloc[i][j];
                seq[count++] = i;
                finish[i] = 1;
                found = 1;
            }
        }
        if(!found) {
            printf("\nSystem is NOT in safe state.\n");
            return 0;
        }
    }
    printf("\nSystem is in SAFE state.\nSafe sequence is: ");
    for(i = 0; i < n; i++)
        printf("P%d ", seq[i]);
    printf("\n");
    return 0;
}