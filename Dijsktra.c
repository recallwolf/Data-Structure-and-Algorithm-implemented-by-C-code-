#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 999

struct Graph {
    char VertexNode[100];  //顶点表
    int arc[100][100];  //邻接矩阵，边表
    int numNode, numEdge;  //图中顶点数与边数
};

void createGraph(struct Graph **G, char arr[]) {
    *G = (struct Graph *)malloc(sizeof(struct Graph));
    (*G)->numNode = strlen(arr);

    for (int i = 0; i < (*G)->numNode; i++) {
        (*G)->VertexNode[i] = arr[i];
        for(int j = 0; j < (*G)->numNode; j++) {
            (*G)->arc[i][j] = INF;
        }
    }

    int edge[][3] = {
        {0, 1, 4}, 
        {0, 3, 6}, 
        {0, 2, 6}, 
        {1, 2, 1}, 
        {1, 4, 7}, 
        {3, 2, 2},
        {3, 5, 5},
        {2, 4, 6},
        {2, 5, 4},
        {4, 6, 6},
        {5, 4, 1},
        {5, 6, 8}
    };

    (*G)->numEdge = (sizeof(edge) / sizeof(int)/3);
    for (int i = 0; i < (*G)->numEdge; i++) {
        (*G)->arc[edge[i][0]][edge[i][1]] = edge[i][2];
    }
}

void Dijsktra(struct Graph *G, int len, int path[]) {
    int cost[len], visitedNode[len];
    int index = 0;
    int lowestIndex, min;
    for(int i = 0; i < len; i++) {
        cost[i] = G->arc[index][i];
        visitedNode[i] = 0;
        if (G->arc[index][i] != INF) {
            path[i] = index;
        }
        else {
            path[i] = -1;
        }
    }
    visitedNode[index] = 1;
    path[index] = -1;
    for(int i = 0; i < len - 1; i++) {
        min = INF;
        for (int j = 0; j < len; j++) {
            if (visitedNode[j] != 1 && cost[j] < min) {
                min = cost[j];
                lowestIndex = j;
            }
        }
        visitedNode[lowestIndex] = 1;
        index = lowestIndex;
        for (int j = 0; j < len; j++) {
            //判断下一节点是否访问，到index的最短路径 + index到j的长度是否小于起始点到j的长度
            if (visitedNode[j] != 1 && cost[index] + G->arc[index][j] < cost[j]) {
                //更新最短路径数组
                cost[j] = cost[index] + G->arc[index][j];
                //index结点指向j结点
                path[j] = index;
            }
        }
    }
}

//递归打印路径
void PrintPath(int len, int path[], int index) {
    if (path[index] > 0) {
        printf("%d", path[index]); 
        PrintPath(len, path, path[index]);
    }
};
void main() {
    struct Graph *G;
    char VertexNode[] = "ABCDEFG";
    char len = strlen(VertexNode);
    createGraph(&G, VertexNode);
    int path[G->numEdge];
    Dijsktra(G, len, path);
    printf("6");
    PrintPath(len, path, path[len - 1]);
    printf("0");
}