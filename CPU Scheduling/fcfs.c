#include <stdio.h>
#include <stdlib.h>
struct p{
    int arrival, id, burst, waiting, tat;
};
int cmpfnc1(const void* a, const void* b){
    struct p* A = (struct p*)a;
    struct p* B = (struct p*)b;
    if (A-> arrival > B->arrival) return 1;
    if (B-> arrival > A->arrival) return -1;
    if (A->arrival == B->arrival) return A->id - B->id;
}
int cmpfnc2(const void* a, const void* b){
  struct p* A = (struct p*)a;
  struct p* B = (struct p*)b;
  return A->id - B->id;
}
void calc(struct p arr[],int n){
    qsort(arr, n, sizeof(struct p), cmpfnc1);
    int time = 0;
    float avg_tat = 0.0, avg_wait = 0.0;
    for(int i=0; i < n; i++){
        time+= arr[i].burst;
        arr[i].tat = time - arr[i].arrival;
        arr[i].waiting = arr[i].tat - arr[i].burst;
        avg_tat+= arr[i].tat, avg_wait+= arr[i].waiting;
    }
    printProcess(arr, n);
    printf("Average turnaround time = %.2f\n",avg_tat/n );
    printf("Average waiting time = %.2f\n",avg_wait/n );
}
void printProcess(struct p arr[],int n){
    qsort(arr, n, sizeof(struct p), cmpfnc2);
    printf("Process : \n");
    printf("Process_ID Arrival Burst  TAT Waiting\n");
    for(int i=0; i < n; i++) printf("\t%d\t%d    %d    %d   %d\n",arr[i].id, arr[i].arrival, arr[i].burst, arr[i].tat, arr[i].waiting);
}
int main(){
    int n;
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    struct p arr[n];
    for(int i=0; i < n; i++){
        printf("Enter arrival time for P%d : ", i+1);
        scanf("%d",&arr[i].arrival);
        printf("Enter burst time for P%d : ", i+1);
        scanf("%d",&arr[i].burst);
        arr[i].id = i + 1;
    }
    calc(arr, n);
    return 0;
}
