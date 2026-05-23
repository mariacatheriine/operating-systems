#include <stdio.h>
#define MAX 10
int main() {
    int n, m, i, j;
    int alloc[MAX][MAX], request[MAX][MAX], avail[MAX];
    int finish[MAX];
    printf("Enter number of processes: ");    scanf("%d", &n);
    printf("Enter number of resource types: "); scanf("%d", &m);
    printf("\nEnter Allocation matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    printf("\nEnter Request matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &request[i][j]);
    printf("\nEnter Available resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);
    for(i = 0; i < n; i++) {
        for(j = 0; j < m && alloc[i][j] == 0; j++);
        finish[i] = (j == m) ? 1 : 0;
    }
    int found;
    do {
        found = 0;
        for(i = 0; i < n; i++) {
            if(finish[i]) continue;
            for(j = 0; j < m && request[i][j] <= avail[j]; j++);
            if(j == m) {
                for(j = 0; j < m; j++)
                    avail[j] += alloc[i][j];
                finish[i] = 1;
                found = 1;
            }
        }
    } while(found);
    int deadlock = 0;
    for(i = 0; i < n; i++) {
        if(!finish[i]) {
            deadlock = 1;
            printf("Process P%d is deadlocked\n", i);
        }
    }
    if(!deadlock)
        printf("System is NOT deadlocked\n");

    return 0;
}