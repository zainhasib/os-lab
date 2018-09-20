#include<stdio.h>
#include<stdlib.h>

int n = 6;
int current_time = 0;
int f=0;
int a=0;
int o=0;

typedef struct {
    int pid;
    int at;
    int bt;
    int rt;
    int complete;
} PROCESS;

typedef struct {
    int pid;
    int st;
    int end;
}OUTPUT;

// Processes 
PROCESS process[6]={{0,0,6,6,0}, {1,9,7,7,0}, {2,15,7,7,0}, {3,10,10,10,0}, {4,17,5,5,0}, {5,13,8,8,0}};
PROCESS filter[6];
PROCESS arrived[6];
PROCESS smallest;

// Output
OUTPUT output[100];

void printProcesses() {
    int i = 0;
    for(i=0;i<6;i++) {
        printf("Process : %d\n", process[i].pid);
    }
}

void printOutput() {
    int i = 0;
    for(i=0;i<o;i++) {
        printf("Process : %d , Start : %d, End : %d\n", output[i].pid, output[i].st, output[i].end);
    }
}


int getCompleted() {
    int i,j;
    int count=0;
    for(i=0;i<6;i++) {
        if(process[i].complete) {
            count++;
        }
    }
    return count;
}

void resetArrived() {
    int i=0;
    for(i=0;i<6;i++) {
        arrived[i].at = 0;
        arrived[i].bt = 0;
        arrived[i].pid = 0;
        arrived[i].complete = 0;
    }
}

void resetFilter() {
    int i=0;
    for(i=0;i<6;i++) {
        filter[i].at = 0;
        filter[i].bt = 0;
        filter[i].pid = 0;
        filter[i].complete = 0;
    }
}

void getArrived() {
    int i=0;
    a=0;
    for(i=0;i<6;i++) {
        if(process[i].at <= current_time) {
            arrived[a] = process[i];
            a++;
        }
    }
}

void setFilter() {
    int i=0;
    f=0;
    for(i=0;i<a;i++) {
        if(!process[arrived[i].pid].complete) {
            filter[f] = arrived[i];
            f++;
        }
    }
}

double absoluteDiff(int a, double b) {
    double diff=0;
    diff = a-b;
    if(diff<0) {
        diff=(-diff);
    }
    return diff;
}

typedef struct {
    int m;
    int pid;
}MINPR;

MINPR min;

PROCESS findMean() {
    int i=0,j=0;
    double mean=0;
    for(i=0;i<f;i++) {
        j+=filter[i].bt;
    }
    mean = j/(double)f;
    int m;
    min.m = 10000;
    for(i=0;i<f;i++) {
        if(min.m > absoluteDiff(filter[i].rt, mean)) {
            min.m = absoluteDiff(filter[i].rt, mean);
            min.pid = filter[i].pid;
            m=absoluteDiff(filter[i].rt, mean);
        }
    }
    printf("%lf %d %d\n", mean, min.pid, min.m);
    return process[min.pid];
}


void setOutput() {
    smallest = findMean();
    if(filter[0].complete) {
        printf("\nDAMn\n");
    }
    output[o].pid = smallest.pid;
    output[o].st = current_time;
    output[o].end = current_time + 1;
    process[smallest.pid].rt--;
    if(process[smallest.pid].rt <= 0) {
        //printf("R time: %d\n", process[smallest.pid].rt);
        process[smallest.pid].complete = 1;
    }
    o++;
}

void printFilter() {
    int i = 0;
    for(i=0;i<f;i++) {
        printf("Filter Process : %d\n", filter[i].pid);
    }
}

int main(int argc, char const *argv[])
{
    printProcesses();
    printf("\n");

    while(getCompleted() < 6) {
        resetArrived();
        getArrived();
        resetFilter();
        setFilter();
        //printFilter();
        if(f>0) {
            setOutput();
        }
        current_time++;
    }

    printOutput();

    return 0;
}