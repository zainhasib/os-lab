#include<stdio.h>
#include<stdlib.h>

int n = 5;
int a=0;
int f=0;
int o=0;
int current_time=0;
int last_process_end=0;

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
PROCESS process[5]={{0,2,3,0,0}, {1,3,9,0,0}, {2,0,6,0,0}, {3,1,2,0,0}, {4,25,8,0,0}};
PROCESS arrived[5], filter[5], rest[5];

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

void heapifyRest(int n, int i) {
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
 
    if (l < n && rest[l].at > rest[largest].at)
        largest = l;
 
    if (r < n && rest[r].at > rest[largest].at)
        largest = r;
 
    if (largest != i)
    {
        PROCESS temp;
        temp = rest[i];
        rest[i] = rest[largest];
        rest[largest] = temp;
 
        heapifyRest(n, largest);
    }
}

void heapifyFilter(int n, int i) {
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
 
    if (l < n && filter[l].bt < filter[largest].bt)
        largest = l;
 
    if (r < n && filter[r].bt < filter[largest].bt)
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

void buildHeapFilter(int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyFilter(n, i);
}

void buildHeap(int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);
}

void buildHeapRest(int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyRest(n, i);
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

void resetFilter() {
    int i=0;
    for(i=0;i<5;i++) {
        filter[i].pid = 0;
        filter[i].at = 0;
        filter[i].bt = 0;
    }
}

void setFilter() {
    int i=0;
    int p,q;
    f=0;
    for(i=0;i<a;i++) {
        if(!process[arrived[i].pid].complete) {
            filter[f] = arrived[i];
            f++;
        }
    }
}

void addArrived() {
    int p,q;
    int arr = 0;
    int i=0;
    for(p=0;p<5;p++) {
        if(current_time >= process[p].at && !process[p].arrived) {
            arr = 1;
            process[p].arrived = 1;
            arrived[a] = process[p]; 
            a++;
        }
    }
    if(arr==0) {
        int r=0;
        for(i=0;i<5;i++) {
            if(!process[i].complete) {
                rest[r] = process[i];
                r++;
            }
        }
        buildHeapRest(r);
        current_time = rest[0].at;
    }
}

void addOutput() {
    int i,j;
    if(process[filter[0].pid].complete) {
        printf("Already  Done");
    }else {
        output[o].pid = filter[0].pid;
        int max_time = filter[0].at > last_process_end ? filter[0].at : last_process_end;
        output[o].st = max_time;
        output[o].end = max_time + filter[0].bt;
        current_time = output[o].end;
        last_process_end = output[o].end;
        //printf("%d", last_process_end);
        process[filter[0].pid].complete = 1;
        filter[0].complete = 1;
        o++;
    }
    
}

void printProcesses() {
    int i = 0;
    for(i=0;i<5;i++) {
        printf("Process : %d Complete %d\n", process[i].pid, process[i].complete);
    }
}

void printOutput() {
    int i = 0;
    for(i=0;i<5;i++) {
        printf("Process : %d , Start : %d, End : %d\n", output[i].pid, output[i].st, output[i].end);
    }
}

void printFilterItem() {
    int i = 0;
    printf("Filter Process : %d , Start : %d, End : %d\n", filter[0].pid, filter[0].at, filter[0].bt);
}

int main(int argc, char const *argv[])
{
    printProcesses();

    heapSort(n);

    printf("\n");

    printProcesses();

    printf("\n");

    while(o!=5) {
        addArrived();
        resetFilter();
        setFilter();
        buildHeapFilter(f);
        addOutput();
    }
    printProcesses();

    printOutput();

    return 0;
}