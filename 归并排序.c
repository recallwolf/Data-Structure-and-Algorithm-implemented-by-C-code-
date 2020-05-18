#include <stdio.h>

void merge(int arr[], int left, int pivot, int right) {
   
    int leftLen = pivot - left + 1;  //左数组长度
    int rightLen = right - pivot;  //右数组长度
    int leftArr[leftLen], rightArr[rightLen];

    for(int i = 0; i < leftLen; i++) {
        leftArr[i] = arr[left + i];
    }

    for(int i = 0; i < rightLen; i++) {
        rightArr[i] = arr[pivot + i + 1];
    }

    int leftIndex = 0;
    int rightIndex = 0; 
    int mainIndex = left;   //主数组初始下标为left，即分区后的最左元素下标

    while(leftIndex < leftLen && rightIndex < rightLen) {
        //对比左右两数组值大小，找到相比较小的值，放入主数组中
        if (leftArr[leftIndex] <= rightArr[rightIndex]) {
            arr[mainIndex] = leftArr[leftIndex];
            leftIndex++;
        }
        else if (leftArr[leftIndex] > rightArr[rightIndex]) {
            arr[mainIndex] = rightArr[rightIndex];
            rightIndex++;
        }
        mainIndex++;
    }
    //当两数组中的一个比较完，放入主数组，另一数组剩余元素依次全部放入主数组中
    while(leftIndex < leftLen) {
        arr[mainIndex] = leftArr[leftIndex];
        mainIndex++;
        leftIndex++;
    }
    while(rightIndex < rightLen) {
        arr[mainIndex] = rightArr[rightIndex];
        mainIndex++;
        rightIndex++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if(left < right) {  //最小分区不能小于1
        int pivot = (right - left) / 2 + left;  //中间值
        mergeSort(arr, left, pivot);  //左侧数组不断细分
        mergeSort(arr, pivot + 1, right);  //右侧数组不断细分
        merge(arr, left, pivot, right); 
    }
}

void main() {
    int merge[] = {32,78,10,5,66,125,9,55};
    int mergeLen = sizeof(merge) / sizeof(int);
    mergeSort(merge, 0, mergeLen - 1);
    printf("归并排序结果：");
    for (int i = 0; i < mergeLen; i++) {
       printf("%d ",merge[i]);
   }
}