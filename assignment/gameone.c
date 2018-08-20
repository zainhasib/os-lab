#include<stdio.h>
#include<stdlib.h>

void printarray(int array[8][2]) {
    int i=0,j=0;
    for(i=0;i<2;i++) {
        printf("%d ", array[i][0]);
    }
}

int main(int argc, char const *argv[])
{
    int array[8][2] = {1,2,3,4,5,6,7,8, 1,2,3,4,5,6,7,8};
    printarray(array);
    return 0;
}
