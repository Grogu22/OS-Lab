#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct p{
  int arrival, id, burst, waiting, tat, na, nb;
};
int cmpfnc1(const void* a, const void* b){
  struct p* A = (struct p*)a;
  struct p* B = (struct p*)b;
  if (A-> arrival > B->arrival) return 1;
  if (A-> arrival < B->arrival) return -1;
  if (A->arrival == B->arrival) return A->id > B->id ? 1 : -1;
}
int cmpfnc2(const void* a, const void* b){
  struct p* A = (struct p*)a;
  struct p* B = (struct p*)b;
  return A->id - B->id;
}
int cmpfnc3(const void* a, const void* b){
  struct p* A = (struct p*)a;
  struct p* B = (struct p*)b;
  return A->na > B->na ? 1 : -1;
}
int total_time(struct p arr[], int n){
  int init_time = 0;
  for(int i=0; i < n; i++) init_time+= arr[i].burst;
  return init_time;
}
int return_blocks(struct p arr[], int n, int tq){
  int blocks = 0;
  for(int i=0; i < n; i++) {
    if(arr[i].burst > tq )blocks+= (int)ceil((double)arr[i].burst / tq);
    else if (arr[i].burst <= tq) blocks+= 1;
  } return blocks;
}
void printProcess(struct p arr[],int n){
    qsort(arr, n, sizeof(struct p), cmpfnc2);
    printf("Process : \n");
    printf("Process_ID Arrival Burst  TAT Waiting\n");
    for(int i=0; i < n; i++) printf("\t%d\t%d    %d    %d   %d\n",arr[i].id, arr[i].arrival, arr[i].burst, arr[i].tat, arr[i].waiting);
}
void gantt(struct p arr[], int n, int tq){
  qsort(arr,n, sizeof(struct p), cmpfnc1);
  int total_burst = total_time(arr, n);
  int init_time = 0,j=0, block_size = return_blocks(arr,n, tq);
  struct p* rq = (struct p*)malloc(sizeof(struct p) *block_size);
  for(int i=0; i < n , init_time < total_burst && j < block_size; i++ ){
    label : printf("");
    if (i > 0) qsort(arr, i,sizeof(struct p), cmpfnc3);
    for(int k = 0; k < i; k++){
      if(arr[k].na < arr[i].na && arr[k].nb > 0){
        if(arr[k].nb <= tq) init_time += arr[k].nb, arr[k].nb = 0, arr[k].na = arr[k].tat = init_time;
        else if (arr[k].nb > tq) init_time+= tq, arr[k].nb -= tq, arr[k].na = arr[k].tat = init_time ;
        rq[j++] = arr[k];
      }
    }
    if (arr[i].nb > 0){
      if(arr[i].nb <= tq) init_time += arr[i].nb, arr[i].nb = 0, arr[i].na = arr[i].tat = init_time;
      else if (arr[i].nb > tq) init_time+= tq, arr[i].nb -= tq, arr[i].na = arr[i].tat = init_time ;
      rq[j++] = arr[i];}
      if (i == n-1 && init_time < total_burst) goto label;
  }
  qsort(arr, n, sizeof(struct p),cmpfnc2);
}
void calc(struct p arr[],int n){
    float avg_tat = 0.0, avg_wait = 0.0;
    for(int i=0; i < n; i++){
        arr[i].tat-= arr[i].arrival;
        arr[i].waiting = arr[i].tat - arr[i].burst;
        avg_tat+= arr[i].tat, avg_wait+= arr[i].waiting;
    }
    printProcess(arr, n);
    printf("Average turnaround time = %.2f\n",avg_tat/n );
    printf("Average waiting time = %.2f\n",avg_wait/n );
}
int main(){
    int n, tq;
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    printf("Enter time quantum : ");
    scanf("%d",&tq);
    struct p arr[n];
    for(int i=0; i < n; i++){
        printf("Enter arrival time for P%d : ", i+1);
        scanf("%d",&arr[i].arrival);
        printf("Enter burst time for P%d : ", i+1);
        scanf("%d",&arr[i].burst);
        arr[i].id = i + 1, arr[i].na = arr[i].arrival, arr[i].nb = arr[i].burst,arr[i].tat = 0;
    }
    gantt(arr, n, tq);
    calc(arr, n);
    return 0;
}
