#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Graph {
    char VertexNode[100];  //顶点表
    int arc[100][100];  //邻接矩阵，边表
    int numNode, numEdge;  //图中顶点数与边数
};

struct Queue {
    int front, rear;
    char data[100]; 
};

void InitQueue(struct Queue *Q) {
    Q->front = 0;
    Q->rear = 0; 
}

void EnQueue(struct Queue *Q, char data) {
    if (Q->rear == 99) {
        printf("error");
    }
    else {
        Q->data[(Q->rear)++] = data;
    }   
}

char DeQueue(struct Queue *Q) {
    return Q->data[(Q->front)++];
}

void createGraph(struct Graph **G, char arr[]) {
    *G = (struct Graph *)malloc(sizeof(struct Graph));
    (*G)->numNode = strlen(arr);

    for (int i = 0; i < (*G)->numNode; i++) {
        (*G)->VertexNode[i] = arr[i];  //节点赋值
        for(int j = 0; j < (*G)->numNode; j++) {
            (*G)->arc[i][j] = 0;    //边赋值，此处无权值
        }
    }

    int edge[][2] = {
        {0, 3}, 
        {1, 2}, 
        {1, 0}, 
        {2, 0}, 
        {2, 1}, 
        {3, 2}
    };

    (*G)->numEdge = (sizeof(edge) / sizeof(int)/2);
    for (int i = 0; i < (*G)->numEdge; i++) {
        (*G)->arc[edge[i][0]][edge[i][1]] = 1; //构造邻接矩阵
    }
}

char vistedDFS[100];  //辅助数组，判断节点是否访问过
void DFS(struct Graph **G, int i) {
    vistedDFS[i] = 1;
    printf("%c", (*G)->VertexNode[i]);
    for(int j = 0; j < (*G)->numNode; j++) {
        if(!vistedDFS[j] && (*G)->arc[i][j] == 1) {
            DFS(G, j);  //j为下个节点下标
        }
    }
}

void DFSTravers(struct Graph **G) {
    for (int i = 0; i < (*G)->numNode; i++) {
        if (!vistedDFS[i]) {  //判断节点是否访问
            DFS(G, i);
        }
    }
}

char visitedBFS[100];  //辅助数组，判断节点是否访问过
void BFS(struct Graph **G, int i, struct Queue *Q) {
    EnQueue(Q,(*G)->VertexNode[i]);
    while(Q->front != Q->rear) {  //队列不为空，则继续下一步
        char VertexNode = DeQueue(Q);
        printf("%c", VertexNode);
        for (int j = 0; j < (*G)->numNode; j++) {
            if (!visitedBFS[j] && (*G)->arc[i][j] == 1) {
                visitedBFS[j] = 1;
                EnQueue(Q,(*G)->VertexNode[j]);
            }
        }
    }
}

void BFSTravers(struct Graph **G) {
    struct Queue *qhead = (struct Queue *)malloc(sizeof(struct Queue));
    InitQueue(qhead);
    for (int i = 0; i < (*G) -> numNode; i++) {
        if (!visitedBFS[i]) {  //判断节点是否访问
            visitedBFS[i] = 1;
            BFS(G, i, qhead);
        }
    }
}

void main() {
    struct Graph *G;
    char VertexNode[] = "ABCD";
    createGraph(&G, VertexNode);
    printf("DFS遍历结果：");
    DFSTravers(&G);
    printf("\n");
    printf("BFS遍历结果：");
    BFSTravers(&G);
}