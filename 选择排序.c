#include <stdio.h>

void selectSort(int arr[], int arrLen) {
    int i, j, temp;
    for (i = 0; i < arrLen - 1; i++) {  //选择从第一个元素开始，找到最小元素与此位进行换位，一共需要选择arrLen - 2次（arrLen-1个元素，最后一个元素不需要选择比较）
        int min = i;  
        for (j = i + 1; j < arrLen; j++) {  //从所需比较的元素后一位开始比较，找到比所需比较元素小的元素，记录下标，循环结束找到当前最小元素下标
            if (arr[min] > arr[j]) {  
                min = j;  
            }
        }
        if (min != i) { //如果最小元素发生了改变，则交换两值，从而把[最小，次小，次次小......]的值换入数组前列相应位置
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

void heapify(int arr[], int arrLen, int parent) {
    int lchild = parent * 2 + 1;    //父节点的左子节点
    int rchild = parent * 2 + 2;    //父节点的右子节点
    int max = parent;
    if (parent < arrLen) {  //父节点下标不超过数组总长度
        //找到父节点、左子节点、右子节点中最大的值
        if (lchild < arrLen && arr[lchild] > arr[max]) {  
            max = lchild;
        }
        if (rchild < arrLen && arr[rchild] > arr[max]) {
            max = rchild;
        }
        if (max != parent) {  //如果最大的值不是父节点
            int temp = arr[parent];
            arr[parent] = arr[max];
            arr[max] = temp; 
            heapify(arr, arrLen, max);  //交换值对堆的形态产生了改变，需要对父节点以及所有子节点重新堆化处理
        }
    }
}

void heapSort(int arr[], int arrLen) {

    int lastNode = arrLen - 1;  //获取最后一个节点
    int parent = (lastNode - 1) / 2;  //最后一个节点的父节点
    for (int i = parent; i >= 0; i--) { //从最后一个节点的父节点做heapify，直到根节点
        heapify(arr, arrLen, i);
    }

    for (int i = lastNode; i >= 0; i--) {   //把最后一节点与根节点进行交换，即把最大值放入最后一个节点
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        heapify(arr, i, 0); //对除开最有一个元素（即最大元素）的树重新堆化，找到新一个最大的值（即根节点值）
    }
}

void main() {
    int select[] = {32,78,10,5,66,125,9,55};
    int selectLen = sizeof(select) / sizeof(int);
    selectSort(select, selectLen);
    printf("选择排序结果：");
    for (int i = 0; i < selectLen; i++) {
        printf("%d ",select[i]);
   }

    printf("\n");

    int heap[] = {32,78,10,5,66,125,9,55};
    int heapLen = sizeof(heap) / sizeof(int);
    heapSort(heap, heapLen);
    heapify(heap,0, heapLen);
    printf("堆排序结果：");
    for (int i = 0; i < heapLen; i++) {
        printf("%d ",heap[i]);
   }
}