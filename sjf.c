#include<stdio.h>
#include<stdlib.h>

int n = 5;
int k=0;

typedef struct {
    int pid;
    int at;
    int bt;
    int complete;
} PROCESS;

typedef struct {
    int pid;
    int st;
    int ct;
}OUTPUT;

PROCESS process[5]={{0,2,3,0}, {1,3,9,0}, {2,0,6,0}, {3,1,2,0}, {4,5,8,0}};
OUTPUT output[5];
PROCESS filter[5];

void heapify(int n, int i) {
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
 
    if (l < n && process[l].at > process[largest].at)
        largest = l;
 
    if (r < n && process[r].at > process[largest].at)
        largest = r;
 
    if (largest != i)
    {
        PROCESS temp;
        temp = process[i];
        process[i] = process[largest];
        process[largest] = temp;
 
        heapify(n, largest);
    }
}

void buildHeap(int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);
}
void heapifyFilter(int n, int i) {
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
 
    if (l < n && filter[l].bt > filter[largest].bt)
        largest = l;
 
    if (r < n && filter[r].bt > filter[largest].bt)
        largest = r;
 
    if (largest != i)
    {
        PROCESS temp;
        temp = filter[i];
        filter[i] = filter[largest];
        filter[largest] = temp;
 
        heapifyFilter(n, largest);
    }
}

void buildHeapFilter(int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyFilter(n, i);
}

void heapifyBurstTime(int n, int i) {
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
 
    if (l < n && process[l].bt > process[largest].bt)
        largest = l;
 
    if (r < n && process[r].bt > process[largest].bt)
        largest = r;
 
    if (largest != i)
    {
        PROCESS temp;
        temp = process[i];
        process[i] = process[largest];
        process[largest] = temp;
 
        heapifyBurstTime(n, largest);
    }
}

void buildHeapBurstTime(int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyBurstTime(n, i);
}

void heapSort(int n) {

    buildHeap(n);

    for (int i=n-1; i>=0; i--)
    {
        PROCESS temp;
        temp = process[0];
        process[0] = process[i];
        process[i] = temp;

        heapify(i, 0);
    }
}
void heapSortFilter(int n) {

    buildHeapFilter(n);

    for (int i=n-1; i>=0; i--)
    {
        PROCESS temp;
        temp = filter[0];
        filter[0] = filter[i];
        filter[i] = temp;

        heapifyFilter(i, 0);
    }
}

void heapSortBurstTime(int n) {

    buildHeapBurstTime(n);

    for (int i=n-1; i>=0; i--)
    {
        PROCESS temp;
        temp = process[0];
        process[0] = process[i];
        process[i] = temp;

        heapifyBurstTime(i, 0);
    }
}

void printProcesses() {
    int i = 0;
    for(i=0;i<5;i++) {
        printf("Process : %d\n", process[i].pid);
    }
}

void printFilter() {
    int i = 0;
    for(i=0;i<k;i++) {
        printf("Process : %d\n", filter[i].pid);
    }
}

void printOutput() {
    int i = 0;
    for(i=0;i<5;i++) {
        printf("Process : %d , Start : %d, End : %d\n", output[i].pid, output[i].st, output[i].ct);
    }
}

int isComplete(int id) {
    int i;
    for(i=0; i<5; i++) {
        if(output[i].pid == id) {
            return 1;
        }
    }
    return 0;
}


int main(int argc, char const *argv[])
{
    int currentTime=0;
    // Sorted a/c to arrival time
    heapSort(n);
    printProcesses();
    printf("\n");
    heapSortBurstTime(n);
    printProcesses();
    printf("\n");
    while(k!=5) {
        int i=0;
        for(i=0;i<5;i++) {
            if(process[i].at <= currentTime && !isComplete(process[i].pid)) {
                filter[k].pid = process[i].pid;
                filter[k].at = process[i].at;
                filter[k].bt = process[i].bt;
                k++;
            }
        }
        printf("\nk is: %d\n", k);
        printFilter();
        printf("\n");
        heapSortFilter(k);
        printFilter();
        int last=0;
        int last_time=0;
        for(i=0;i<k;i++) {
            output[i].pid = filter[i].pid;
            last_time = filter[i].at > last ? filter[i].at : last;
            output[i].st = last_time;
            output[i].ct = last_time + filter[i].bt;
            last = output[i].ct;
        }
    }
    printOutput();
    return 0;
}
