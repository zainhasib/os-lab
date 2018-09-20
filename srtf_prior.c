#include <stdio.h>
#include <stdlib.h>

int n = 5;
int current_time = 0;
int a = 0;
static int f = 0;
int o = 0;

typedef struct
{
    int pid;
    int at;
    int bt;
    int rt;
    int pri;
    int arrived;
    int complete;
} PROCESS;

typedef struct
{
    int pid;
    int st;
    int end;
} OUTPUT;

// Processes
PROCESS process[5] = {{0, 9, 4, 4, 1, 0, 0}, {1, 0, 8, 8, 3, 0, 0}, {2, 6, 10, 10, 1, 0, 0}, {3, 3, 4, 4, 5, 0, 0}, {4, 4, 2, 2, 2, 0, 0}};
PROCESS arrived[5], filter[5];

// Output
OUTPUT output[100] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

void heapifyFilterBurst(int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && filter[l].rt < filter[largest].rt)
        largest = l;

    if (r < n && filter[r].rt < filter[largest].rt)
        largest = r;

    if (largest != i)
    {
        PROCESS temp;
        temp = filter[i];
        filter[i] = filter[largest];
        filter[largest] = temp;

        heapifyFilterBurst(n, largest);
    }
}

void buildHeapBurst(int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyFilterBurst(n, i);
}

void heapifyFilter(int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && filter[l].pri < filter[largest].pri)
        largest = l;

    if (r < n && filter[r].pri < filter[largest].pri)
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

void buildHeapFilter(int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyFilter(n, i);
}

void addArrived()
{
    int p, q;
    int arr = 0;
    int i = 0;
    for (p = 0; p < 5; p++)
    {
        if (current_time >= process[p].at && !process[p].arrived)
        {
            process[p].arrived = 1;
            arrived[a] = process[p];
            a++;
        }
    }
}

void resetFilter()
{
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        filter[i].pid = 0;
        filter[i].at = 0;
        filter[i].bt = 0;
    }
}

void setFilter()
{
    int i = 0;
    int p, q;
    f = 0;
    for (i = 0; i < a; i++)
    {
        if (!process[arrived[i].pid].complete)
        {
            filter[f] = arrived[i];
            f++;
        }
    }
}

void addOutput()
{
    int i = 0, j = 0;
    if (f > 0)
    {
        int id = filter[0].pid;
        process[id].rt--;
        arrived[id].rt--;
        filter[id].rt--;
        output[o].pid = filter[0].pid;
        output[o].st = current_time;
        output[o].end = current_time + 1;
        if (process[id].rt <= 0)
        {
            process[id].complete = 1;
            arrived[id].complete = 1;
            filter[id].complete = 1;
        }
        o++;
    }
}

int getCompleted()
{
    int i, j;
    int count = 0;
    for (i = 0; i < 5; i++)
    {
        if (process[i].complete)
        {
            count++;
        }
    }
    return count;
}

void printOutput()
{
    int i = 0;
    printf("Output: \n");
    for (i = 0; i < o; i++)
    {
        printf("Process : %d, Start : %d, End : %d\n", output[i].pid, output[i].st, output[i].end);
    }
}

void printProcesses()
{
    int i = 0;
    printf("Processes: \n");
    for (i = 0; i < 5; i++)
    {
        printf("Process : %d, Start : %d, End : %d\n", process[i].pid, process[i].at, process[i].bt);
    }
}

void printFilterItem()
{
    int i = 0;
    printf("Filter Process : %d , Start : %d, End : %d\n", filter[0].pid, filter[0].at, filter[0].bt);
}

int main(int argc, char const *argv[])
{
    printProcesses();

    printf("\n");
    o = 0;
    int r = 0;

    while (getCompleted() < 5)
    {
        addArrived();
        //resetFilter();
        setFilter();
        buildHeapFilter(f);
        //printf("%d\n", filter[0].pid);
        addOutput();
        current_time++;
    }

    printOutput();

    return 0;
}
