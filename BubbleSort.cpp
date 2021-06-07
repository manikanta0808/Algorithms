#include<iostream>
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main(){
    int arr[] = {3,2,4,1,6,7,3,5,61,367,89,23};
    int size = sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<size;i++){
        for(int j=0;j<size-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
    for(int i=0;i<size;i++){
        printf("%d ",arr[i]);
    }printf("\n");
    return 0;
}
/*
    Suppose we have array values 4 3 2 1 5
    Swaps are done as follows 
    initial:    4 3 2 5 1
                3 4 2 5 1
                3 2 4 5 1
                3 2 4 1 5 // 5 is placed correctly 

                2 3 4 1 5
                2 3 1 4 5 // 4 is placed correctly

                2 3 1 4 5
                2 1 3 4 5 // 3 is placed correctly

                1 2 3 4 5// all the array is sorted                
*/
