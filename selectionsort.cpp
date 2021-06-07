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
        int small = i;
        for(int j=i+1;j<size;j++){
            if(arr[small]>arr[j]){
                small = j;
            }
        }swap(&arr[i],&arr[small]);
    }
    for(int i=0;i<size;i++){
        printf("%d ",arr[i]);
    }printf("\n");
    return 0;
}