#include<stdio.h>
#include<stdlib.h>

int n = 5;
int k=0;
int current_time = 0;
int s=0;
int last=0;

typedef struct {
    int pid;
    int at;
    int bt;
    int arrived;
    int complete;
} PROCESS;

typedef struct {
    int pid;
    int st;
    int end;
}OUTPUT;

// Processes 
PROCESS process[5]={{0,2,3,0,0}, {1,3,9,0,0}, {2,0,6,0,0}, {3,1,2,0,0}, {4,7,8,0,0}};
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

void heapifyBurst(PROCESS * filter,int n, int i) {
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
        
        heapify(n, largest);
    }
}

void buildHeapBurst(PROCESS * filter, int n) {
    for (int i = n / 2 - 1; i >= s; i--)
        heapifyBurst(filter, n, i);
}

void heapSortBurst(PROCESS * filter, int n) {

    buildHeapBurst(filter, n);

    for (int i=n-1; i>=s; i--)
    {
        PROCESS temp;
        temp = filter[s];
        filter[s] = filter[i];
        filter[i] = temp;

        heapifyBurst(filter, i, s);
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
            arrived[p].arrived = 1;
            k++;
        }
    }
}

void addOutput() {
    int p,q;
    int max_time;
    PROCESS filter[5];
    int y=0;
    for(p=0;p<k;p++) {
        if(arrived[p].pid > -1 && !arrived[p].complete) {
            filter[y] = arrived[p];
            y++;
        }
    }
    heapSortBurst(filter, y);
    for(p=s;p<k;p++) {
        if(!filter[p].complete) {
            output[p].pid = filter[p].pid;
            max_time = filter[p].at > last ? filter[p].at : last;
            output[p].st = max_time;
            output[p].end = max_time + filter[p].bt;
            last = current_time = output[p].end;
            s=k;
            filter[p].complete = 1;
            addArrived();
        }
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
        //heapSortBurst(k);
        addOutput();
    }

    printOutput();

    return 0;
}