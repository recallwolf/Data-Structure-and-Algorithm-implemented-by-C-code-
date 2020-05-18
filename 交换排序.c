#include <stdio.h>

void bubbleSort(int arr[], int arrLen) {
    int time ;
    int index;
    
    int flag = 1;
    int temp;
    for(time = 1; time < arrLen && flag != 0; time++) {  //从第一轮开始，冒泡排序一共需要arrLen - 1 轮
       flag = 0;  //如果此轮没有进行过一次交换，则表示排序完成，无需继续
       for(index = 0; index <= arrLen - time ; index++ ) {  //从数组下标为0的元素开始交换，每次交换的次数为arrLen - time 次
           if(arr[index] > arr[index+1]) {
               temp = arr[index];
               arr[index] = arr[index+1];
               arr[index+1] = temp;
               flag = 1;  //表明这一轮已发生交换
           }
       }
   }

}

int get_pos(int arr[], int left, int right) {
    int pivot = arr[left];  
    while (left < right) {
        while (arr[right] >= pivot && left < right) {  //如果右元素比中值大，则右指针左移一位，直到左右指针相等或右元素比中值小退出循环
            right--;
        }
        arr[left] = arr[right];  //退出循环时右元素比中值小，右元素放置在中值左边
        while(arr[left] <= pivot && left < right) {  //如果左元素比中值小，则左指针右移一位，直到左右指针相等或左元素比中值大退出循环
            left++;
        }
        arr[right] = arr[left];  //退出循环时左元素比中值大，左元素放置在中值右边
    }
    arr[left] = pivot;  //退出上述循环后，左右指针重合，即为pivot值所在位置
    return left;
}

void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pos = get_pos(arr, left, right);
        quickSort(arr, left, pos - 1);
        quickSort(arr, pos + 1, right);
    }
}

void main() {
    int bubble[] = {32,78,10,5,66,125,9,55};
    int bubLen = sizeof(bubble) / sizeof(int);
    bubbleSort(bubble, bubLen);
    printf("冒泡排序结果：");
    for (int i = 0; i < bubLen; i++) {
       printf("%d ",bubble[i]);
    }

    printf("\n");

    int quick[] = {32,78,10,5,66,125,9,55};
    int quickLen = sizeof(quick) / sizeof(int);
    quickSort(quick, 0, quickLen-1);
    printf("快速排序结果：");
    for (int i = 0; i < quickLen; i++) {
       printf("%d ",quick[i]);
   }
}