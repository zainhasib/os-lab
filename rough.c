#include<stdio.h>
#include<stdlib.h>

struct process {
    int pid;
    int at;
    int bt;
};

struct process p[5];
p[0] = {0,2,3};

void heapify(int arr[], int n, int i)
{
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
 
    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    if (largest != i)
    {
        int temp;
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = arr[i];
 
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    for (int i=n-1; i>=0; i--)
    {
        int temp;
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = arr[0];

        heapify(arr, i, 0);
    }
}

int main() {
    printf("%d", p[0].at);

    return 0;
}