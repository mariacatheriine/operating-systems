#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define CYLINDERS 5000
void generate_requests(int req[])
{
    for(int i=0;i<MAX;i++)
        req[i] = rand() % CYLINDERS;
}
void print_requests(int req[])
{
    printf("Requests: ");
    for(int i=0;i<MAX;i++)
        printf("%d ", req[i]);
    printf("\n");
}
int sstf(int req[], int head)
{
    int visited[MAX]={0};
    int total = 0;
    for(int i=0;i<MAX;i++)
    {
        int min = 100000;
        int index = -1;
        for(int j=0;j<MAX;j++)
        {
            if(!visited[j])
            {
                int dist = abs(head - req[j]);
                if(dist < min)
                {
                    min = dist;
                    index = j;
                }
            }
        }
        total += min;
        head = req[index];
        visited[index] = 1;
    }
    return total;
}
void sort(int arr[])
{
    for(int i=0;i<MAX-1;i++)
        for(int j=0;j<MAX-i-1;j++)
            if(arr[j] > arr[j+1])
            {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
}
int look(int req[], int head)
{
    int total = 0;
    int temp[MAX];
    for(int i=0;i<MAX;i++)
        temp[i] = req[i];
    sort(temp);
    int pos;
    for(int i=0;i<MAX;i++)
        if(temp[i] >= head)
        {
            pos = i;
            break;
        }
    for(int i=pos;i<MAX;i++)
    {
        total += abs(head - temp[i]);
        head = temp[i];
    }
    for(int i=pos-1;i>=0;i--)
    {
        total += abs(head - temp[i]);
        head = temp[i];
    }
    return total;
}
int cscan(int req[], int head)
{
    int total = 0;
    int temp[MAX];
    for(int i=0;i<MAX;i++)
        temp[i] = req[i];
    sort(temp);
    int pos;
    for(int i=0;i<MAX;i++)
        if(temp[i] >= head)
        {
            pos = i;
            break;
        }
    for(int i=pos;i<MAX;i++)
    {
        total += abs(head - temp[i]);
        head = temp[i];
    }
    total += abs(head - (CYLINDERS-1));
    head = 0;
    total += CYLINDERS-1;
    for(int i=0;i<pos;i++)
    {
        total += abs(head - temp[i]);
        head = temp[i];
    }
    return total;
}
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <initial_head>\n", argv[0]);
        return 1;
    }
    int head = atoi(argv[1]);
    int req[MAX];
    srand(time(NULL));
    generate_requests(req);
    print_requests(req);
    printf("SSTF movement: %d\n", sstf(req, head));
    printf("LOOK movement: %d\n", look(req, head));
    printf("CSCAN movement: %d\n", cscan(req, head));
    return 0;
}