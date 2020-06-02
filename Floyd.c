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

// 核心思想 ARC[i][j] > ARC[i][m] + ARC[m][j]
void Floyd(struct Graph *G, int len, int path[][len]) {
    int A[len][len];
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <len; j++) {
            A[i][j] = G->arc[i][j];
            path[i][j] = -1;
        }
    }
    
    for (int m = 0; m < len; m++) {  //m从0开始作为中转结点
        for (int i = 0; i <len; i++) {
            for (int j = 0; j <len; j++) {
                if(A[i][j] > A[i][m] + A[m][j]) {
                    //更新最短路径数组
                    A[i][j] = A[i][m] + A[m][j];
                    path[i][j] = m;
                }
            }
        }
    }
}

//递归打印路径
void PrintPath(int start, int end, int len, int path[][len]) {
    if (path[start][end] == -1) {
        printf("%d", end);
    }
    else {
        int mid = path[start][end];
        PrintPath(start, mid, len, path);
        PrintPath(mid, end, len, path);
    }
}

void main() {
    struct Graph *G;
    char VertexNode[] = "ABCDEFG";
    char len = strlen(VertexNode);
    createGraph(&G, VertexNode);
    int path[len][len];
    Floyd(G, len, path);
    printf("0");
    PrintPath(0, 5, len, path);
    printf("6");
}