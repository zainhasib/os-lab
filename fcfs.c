#include<stdio.h>
#include<stdlib.h>

int n = 5;

typedef struct {
    int pid;
    int at;
    int bt;
} PROCESS;

typedef struct {
    int pid;
    int st;
    int end;
}OUTPUT;

// Processes 
PROCESS process[5]={{0,2,3}, {1,3,9}, {2,0,6}, {3,1,2}, {4,25,8}};

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

int main(int argc, char const *argv[])
{
    printProcesses();

    heapSort(n);

    printf("\n");

    printProcesses();

    printf("\n");

    int i, last = 0;
    int new_time = 0;
    for(i=0; i<5; i++) {
        output[i].pid = process[i].pid;
        new_time = process[i].at > last ? process[i].at : last; 
        output[i].st = new_time;
        output[i].end = new_time + process[i].bt;
        last = output[i].end;
    }

    printOutput();

    return 0;
}