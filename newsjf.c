#include<stdio.h>
#include<stdlib.h>

int n = 5;
int k=0;
int current_time = 0;
int s=0;

typedef struct {
    int pid;
    int at;
    int bt;
    int arrived;
} PROCESS;

typedef struct {
    int pid;
    int st;
    int end;
}OUTPUT;

// Processes 
PROCESS process[5]={{0,2,3,0}, {1,3,9,0}, {2,0,6,0}, {3,1,2,0}, {4,25,8,0}};
PROCESS arrived[5];

// Output
OUTPUT output[5];

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

void heapifyBurst(int n, int i) {
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
        
        heapify(n, largest);
    }
}

void buildHeapBurst(int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyBurst(n, i);
}

void heapSortBurst(int n) {

    buildHeapBurst(n);

    for (int i=n-1; i>=0; i--)
    {
        PROCESS temp;
        temp = process[0];
        process[0] = process[i];
        process[i] = temp;

        heapifyBurst(i, 0);
    }
}

void printProcesses() {
    int i = 0;
    for(i=0;i<5;i++) {
        printf("Process : %d\n", process[i].pid);
    }
}

void printOutput() {
    int i = 0;
    for(i=0;i<5;i++) {
        printf("Process : %d , Start : %d, End : %d\n", output[i].pid, output[i].st, output[i].end);
    }
}

void addArrived() {
    int p,q;
    for(p=0;p<5;p++) {
        if(current_time <= process[p].at && !process[p].arrived) {
            arrived[k] = process[p]; 
            process[p].arrived = 1;
            k++;
        }
    }
}

void addOutput() {
    int p,q;
    int max_time;
    int last=0;
    for(p=s;p<k;p++) {
        output[p].pid = arrived[p].pid;
        max_time = arrived[p].at > last ? arrived[p].at : last;
        output[p].st = max_time;
        output[p].end = max_time + arrived[p].bt;
        last = current_time = output[p].end;
        s=k;
    }
}

int main(int argc, char const *argv[])
{
    printProcesses();

    heapSort(n);

    printf("\n");

    printProcesses();

    printf("\n");

    while(k!=5) {
        addArrived();
    
        addOutput();
    }
    
    printOutput();

    return 0;
}