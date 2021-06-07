#include<iostream>
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main(){
    int arr[] = {3,2,4,1,6,7,3,5,61,367,89,23};
    int size = sizeof(arr)/sizeof(arr[0]);
    for(int i=1;i<size;i++){
        int j = i;
        while(arr[j]<arr[j-1] && j>0){
            swap(&arr[j],&arr[j-1]);
            j--;
        }
    }for(int i=0;i<size;i++){
        printf("%d ",arr[i]);
    }printf("\n");
    return 0;
}