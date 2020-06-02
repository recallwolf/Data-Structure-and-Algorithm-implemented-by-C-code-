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

    (*G)->numEdge = (sizeof(edge) / sizeof(int)/3);
    for (int i = 0; i < (*G)->numEdge; i++) {
        (*G)->arc[edge[i][0]][edge[i][1]] = edge[i][2];
        (*G)->arc[edge[i][1]][edge[i][0]] = edge[i][2];
    }
}

int sum;
void Prim(struct Graph *G, int len) {
    int lowCost[len], visitedNode[len];
    int index = 0;
    int lowestIndex, min;
    for (int i = 0; i < len; i++) {
        lowCost[i] = G->arc[index][i];
        visitedNode[i] = 0;
    }
    visitedNode[index] = 1;
    sum = 0;
    for(int i = 0; i < len - 1; i++) {
        min = INF;
        //找到与第i个节点相邻的最小的边与该边所连节点的下标
        for (int j = 0; j < len; j++) {
            if (visitedNode[j] != 1 && lowCost[j] < min) {
                min = lowCost[j];
                lowestIndex = j;
            }
        }
        visitedNode[lowestIndex] = 1;
        index = lowestIndex;  //移至下一节点
        sum += min; //累加最小边权值
        for (int j = 0; j < len; j++) {
            //如果没有访问过j节点且下一节点到j节点的边权值小于当前lowCost中的最小值,更新lowCost
            if (visitedNode[j] != 1 && G->arc[index][j] < lowCost[j]) {
                lowCost[j] = G->arc[index][j];
            }
        }
    }
}

void main() {
    struct Graph *G;
    char VertexNode[] = "ABCDEF";
    char len = strlen(VertexNode);
    createGraph(&G, VertexNode);
    Prim(G, len);
    printf("%d", sum);
}