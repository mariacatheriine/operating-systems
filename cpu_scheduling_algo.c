#include <stdio.h>
struct Process{
 int pid;
 int at;
 int bt;
 int pr;
 int ct;
 int tat;
 int wt;
 int rt;
};
void sort_by_arrival(struct Process p[], int n){
 struct Process temp;
 for(int i = 0; i < n-1; i++){
  for(int j = 0; j < n-i-1; j++){
   if(p[j].at > p[j+1].at){
    temp = p[j];
    p[j] = p[j+1];
    p[j+1] = temp;
   }
  }
 }
}
void print(struct Process p[], int n, char name[]) {
    float total_tat = 0, total_wt = 0;
    printf("\n\n=== %s Scheduling ===\n", name);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid,
            p[i].at,
            p[i].bt,
            p[i].ct,
            p[i].tat,
            p[i].wt
        );
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("Average TAT = %.2f\n", total_tat / n);
    printf("Average WT  = %.2f\n", total_wt / n);
}
void fcfs(struct Process p[], int n){
 int time = 0;
 for(int i = 0; i < n; i++){
  if(time < p[i].at)
   time = p[i].at;
  time += p[i].bt;
  p[i].ct = time;
  p[i].tat = p[i].ct - p[i].at;
  p[i].wt = p[i].tat - p[i].bt;
 }
}
void srtf(struct Process p[], int n){
 int completed = 0;
 int time = 0;
 while(completed != n){
  int shortest = -1;
  int min_rt = 9999;
  for(int i = 0; i < n; i++){
   if(p[i].at <= time && p[i].rt > 0 && p[i].rt < min_rt){
    min_rt = p[i].rt;
    shortest = i;
   }
  }
  if(shortest == -1){
   time++;
   continue;
  }
  p[shortest].rt--;
  time++;
  if(p[shortest].rt == 0){
   completed++;
   p[shortest].ct = time;
   p[shortest].tat = p[shortest].ct - p[shortest].at;
   p[shortest].wt = p[shortest].tat - p[shortest].bt;
  }
 }
}
void priority_np(struct Process p[], int n){
 int completed = 0;
 int time = 0;
 int visited[20] = {0};
 while(completed != n){
  int highest = -1;
  int max_pr = -1;
  for(int i = 0; i < n; i++){
   if(p[i].at <= time && visited[i] == 0 && p[i].pr > max_pr){
    max_pr = p[i].pr;
    highest = i;
   }
  }
  if(highest == -1){
   time++;
   continue;
  }
  time += p[highest].bt;
  p[highest].ct = time;
  p[highest].tat = p[highest].ct - p[highest].at;
  p[highest].wt = p[highest].tat - p[highest].bt;
  visited[highest] = 1;
  completed++;
 }
}
void round_robin(struct Process p[], int n){
 int time = 0;
 int rem_bt[20];
 for(int i = 0; i < n; i++){
  rem_bt[i] = p[i].bt;
 }
 int done;
 while(1){
  done = 1;
  for(int i = 0; i < n; i++){
   if(rem_bt[i] > 0){
    done = 0;
    if(rem_bt[i] > 3){
     time += 3;
     rem_bt[i] -= 3;
    }
    else{
     time += rem_bt[i];
     p[i].ct = time;
     p[i].tat = p[i].ct - p[i].at;
     p[i].wt = p[i].tat - p[i].bt;
     rem_bt[i] = 0;
    }
   }
  }
  if(done == 1)
   break;
 }
}
int main() {
    int n;
    struct Process p[20], temp[20];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i+1);
        p[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].pr);
    }
    sort_by_arrival(p,n);
    fcfs(temp, n);
    print(temp, n, "FCFS");
    copy(p, temp, n);
    srtf(temp, n);
    print(temp, n, "SRTF");
    copy(p, temp, n);
    priority_np(temp, n);
    print(temp, n, "Priority");
    copy(p, temp, n);
    round_robin(temp, n);
    print(temp, n, "Round Robin");
    return 0;
}