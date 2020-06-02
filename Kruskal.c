#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge {
    int start, end;
    int weight;
};

int edges[][3] = {
        {0, 1, 1}, 
        {0, 2, 2}, 
        {0, 3, 3}, 
        {1, 2, 7}, 
        {1, 4, 8}, 
        {2, 4, 4},
        {2, 3, 6},
        {3, 5, 5},
        {4, 5, 9}
    };

//获取该树的根节点
int getRoot(int p, int parent[]) {
    while(p != parent[p]) {
        p = parent[p];
        return p;
    }
}

//按权值从小到大给边进行排序
void sort(struct Edge arr[], int arrLen) {
    int i, j;
    struct Edge temp;
    for(i = 1; i < arrLen; i++) {  
        temp = arr[i];
        for (j = i - 1; j >= 0 && arr[j].weight > temp.weight; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}

int sum;
void Kruskal(struct Edge edge[], int numNode, int numEdge) {
    int start, end;
    int parent[numNode];
    sum = 0;
    //初始化数组，表明每个结点下标上的值都该节点下标自身即每个节点都是独立节点
    for(int i = 0; i < numNode; i++) {
        parent[i] = i;
    }
    sort(edge, numEdge);
    for(int i = 0; i < numEdge; i++) {
        //分别获取边的开始结点与结束结点的根节点
        start = getRoot(edge[i].start, parent);
        end = getRoot(edge[i].end, parent);
        //如果两结点的根节点不同，则说明是两个不同的集合，则合并
        if (start != end) {
            parent[end] = start;
            sum += edge[i].weight;
        }
    }
}

void main() {
    char VertexNode[] = "ABCDEF";
    int numNode = strlen(VertexNode);
    int numEdge = (sizeof(edges) / sizeof(int)/3);
    int parent[numNode];
    struct Edge edge[numEdge];

    for (int i = 0; i < numEdge; i++) {
        edge[i].start = edges[i][0];
        edge[i].end = edges[i][1];
        edge[i].weight = edges[i][2];
    }

    Kruskal(edge, numNode, numEdge);
    printf("%d", sum);
}