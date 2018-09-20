#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int current_time = 0;
int control = 1;
int a = 0;
int o = 0;

typedef struct {
    int pid;
    int at;
    int bt;
    int rt;
    int arrived;
    int complete;
    int qno;
    int counter;
} PROCESS;

typedef struct {
    int pid;
    int st;
    int end;
} OUTPUT;

typedef struct {
    int qno;
    int qtime;
    int f;
    int r;
    PROCESS p[100];
} QUEUE;

// Processes 
PROCESS process[5]={{0,2,3,3,0,0,0,0}, {1,3,9,9,0,0,0,0}, {2,0,56,56,0,0,0,0}, {3,1,2,2,0,0,0,0}, {4,35,8,8,0,0,0,0}};
PROCESS arrived[5];

OUTPUT output[100];

QUEUE q1, q2, q3;

void enqueue(PROCESS p, int qNo) {
    if(q1.qno == qNo) {
        if(q1.r == -1) {
            q1.f = q1.r = 0;
            p.qno = 1;
            q1.p[q1.f] = p;
        }else {
            q1.r++;
            p.qno = 1;
            q1.p[q1.r] = p;
        }
    }else if(q2.qno == qNo) {
        if(q2.r == -1) {
            q2.f = q2.r = 0;
            p.qno = 2;
            q2.p[q2.f] = p;
        }else {
            q2.r++;
            p.qno = 2;
            q2.p[q2.r] = p;
        }
    }else if(q3.qno == qNo) {
        if(q3.r == -1) {
            q3.f = q3.r = 0;
            p.qno = 3;
            q3.p[q3.f] = p;
        }else {
            q3.r++;
            p.qno = 3;
            q3.p[q3.r] = p;
        }
    }
}

void dequeue(int qNo) {
    if(q1.qno == qNo) {
        if(q1.r == -1) {
            printf("Empty1");
            return;
        }else if(q1.f == q1.r){
            int temp = q1.p[q1.f].pid;
            q1.f = q1.r = -1;
        }else {
            int temp = q1.p[q1.f].pid;
            q1.f++;
        }
    }else if(q2.qno == qNo) {
        if(q2.r == -1) {
            //printf("Empty2");
            return;
        }else if(q2.f == q2.r){
            int temp = q2.p[q2.f].pid;
            q2.f = q2.r = -1;
        }else {
            q2.f++;
        }
    }else if(q3.qno == qNo) {
        if(q3.r == -1) {
            return;
        }else if(q3.f == q3.r){
            int temp = q3.p[q3.f].pid;
            q3.f = q3.r = -1;
        }else {
            int temp = q3.p[q3.f].pid;
            q3.f++;
        }
    }
}

void addArrived() {
    for(int i=0; i<5; i++) {
        if(current_time >= process[i].at && !process[i].arrived) {
            process[i].arrived = 1;
            process[i].qno = 1;
            enqueue(process[i], 1);
            control = 1;
        }
    }
}


int getCompleted() {
    int i,j;
    int count=0;
    for(i=0;i<5;i++) {
        if(process[i].complete) {
            count++;
        }
    }
    return count;
}

void execute() {
    switch(control) {
        case 1 : {
            //printf("\n%d %d %d", q1.p[q1.f].pid, q1.f, q1.r);
            int id = q1.p[q1.f].pid;
            process[id].rt--;
            process[id].counter++;
            output[o].pid = id;
            output[o].st = current_time;
            output[o].end = current_time + 1;
            o++;
            if(process[id].rt > 0 && process[id].counter == q1.qtime) {
                process[id].counter = 0;
                enqueue(process[id], 2);
                dequeue(1);
            }else if(process[id].rt <= 0){
                process[id].complete = 1;
                dequeue(1);
            }
            if(q1.f == -1) {
                control = 2;
            }
            break;
        }
        case 2 : {
            int id = q2.p[q2.f].pid;
            if(q2.r == -1) {
                id = -1;
            }
            process[id].rt--;
            process[id].counter++;
            output[o].pid = id;
            output[o].st = current_time;
            output[o].end = current_time + 1;
            o++;
            if(process[id].rt > 0 && process[id].counter == q2.qtime) {
                process[id].counter = 0;
                enqueue(process[id], 3);
                dequeue(2);
            }else if(process[id].rt <= 0){
                process[id].complete = 1;
                dequeue(2);
            }
            if(q2.f == -1) {
                control = 3;
            }
            break;
        }
        case 3 : {
            int id = q3.p[q3.f].pid;
            if(q3.r == -1) {
                id = -1;
            }
            process[id].rt--;
            process[id].counter++;
            output[o].pid = id;
            output[o].st = current_time;
            output[o].end = current_time + 1;
            o++;
            if(process[id].rt > 0 && process[id].counter == q2.qtime) {
                process[id].counter = 0;
                enqueue(process[id], 1);
                dequeue(3);
                control = 1;
            }else if(process[id].rt <= 0){
                process[id].complete = 1;
                dequeue(3);
            }
            if(q3.f == -1) {
                control = 1;
            }
            break;
        }
    }

}

void printOutput() {
    int i=0;
    printf("Output: \n");
    for(i=0;i<o;i++) {
        if(output[i].pid == -1) {
            printf("No Operation, Start : %d, End : %d\n", output[i].st, output[i].end);
        }else {
            printf("Process : %d, Start : %d, End : %d\n", output[i].pid, output[i].st, output[i].end);
        }
    }
}

int main(int argc, char const *argv[])
{
    q1.r = -1; q1.f = -1, q1.qno = 1, q1.qtime = 4;
    q2.r = -1; q2.f = -1, q2.qno = 2, q2.qtime = 8;
    q3.r = -1; q3.f = -1, q3.qno = 3, q3.qtime = 12;

    while(getCompleted() < 5) {
        addArrived();
        execute();
        current_time++;
    }

    printOutput();

    return 0;
}
