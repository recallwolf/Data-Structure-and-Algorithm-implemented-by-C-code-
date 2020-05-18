#include <stdio.h>

void insertSort(int arr[], int arrLen) {
    int i, j, temp;
    for(i = 1; i < arrLen; i++) {  //一共需要插入arrLen-1次
        temp = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > temp; j--) {  //每次需插入的元素与之前序列元素（已为有序序列）进行比较，如果小于前序列，找到插入位置，插入位置后面元素后移一位。
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}

void shellSort(int arr[], int arrLen) {
    int i, j , increment, temp;
    for (increment = arrLen / 2; increment > 0; increment /= 2) {  //初始间隔为数组长度，每次间隔折半
        for (i = increment; i < arrLen ; i ++) {  //在每个区域进行遍历比较
            temp = arr[i];
            for(j = i- increment; j >=0 && arr[j] > temp; j -= increment) {  //对每间隔相同的元素进行比较，进行插入排序，满足条件所有元素后移一位
                arr[j + increment] = arr[j];
            }
            arr[j + increment] = temp; 
        }
    }
}

void main() {
    int insert[] = {32,78,10,5,66,125,9,55};
    int insLen = sizeof(insert) / sizeof(int);
    insertSort(insert, insLen);
    printf("直接插入排序结果：");
    for (int i = 0; i < insLen; i++) {
       printf("%d ",insert[i]);
   }

    printf("\n");

    int shell[] = {32,78,10,5,66,125,9,55};
    int shellLen = sizeof(insert) / sizeof(int);
    shellSort(shell, shellLen);
    printf("希尔排序结果：");
    for (int i = 0; i < shellLen; i++) {
       printf("%d ",shell[i]);
   }
}