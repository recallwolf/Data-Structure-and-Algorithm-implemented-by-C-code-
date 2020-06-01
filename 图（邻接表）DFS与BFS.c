#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//图结点
struct VertexNode {
    char data;
    struct EdgeNode *firstEdge; 
};

//图边
struct EdgeNode {
    int adjvex;
    int weight;
    struct EdgeNode *next;
};

//图
struct Graph {
    struct VertexNode adjList[10];
    int numVertex, numEdge;
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
    (*G) -> numVertex = strlen(arr);
    for (int i = 0; i < (*G) -> numVertex; i++) {
        (*G) -> adjList[i].data = arr[i]; //节点赋值
    }
    int edge[][2] = {
        {0, 3}, 
        {1, 2}, 
        {1, 0}, 
        {2, 0}, 
        {2, 1}, 
        {3, 2}
    };
    (*G) -> numEdge =   (sizeof(edge) / sizeof(int)/2);

    for(int i = 0; i < (*G) -> numEdge; i++) {
        (*G)->adjList[i].firstEdge = NULL; //节点指针指向空
        struct EdgeNode *e = (struct EdgeNode *)malloc(sizeof(struct EdgeNode));
        e -> adjvex = edge[i][1];  //边赋值
        //链表头插法
        e -> next = (*G) -> adjList[edge[i][0]].firstEdge;
        (*G) -> adjList[edge[i][0]].firstEdge = e;
    }
}

char vistedDFS[100];
void DFS(struct Graph **G, int i) {
    vistedDFS[i] = 1;
    printf("%c", (*G)->adjList[i].data);
    struct EdgeNode *p = (*G)->adjList[i].firstEdge;
    while(p) {
        if (!vistedDFS[p->adjvex]) {
            DFS(G, p->adjvex);  //p_>adjvex为下一节点下标
        }
        p = p->next;  //指向下一条边
    }
}

void DFSTravers(struct Graph **G) {
    for (int i = 0; i < (*G)->numVertex; i++) {
        if (!vistedDFS[i]) {  //判断节点是否访问
            DFS(G, i);
        }
    }
}

char visitedBFS[100];
void BFS(struct Graph **G, int i, struct Queue *Q) {
    EnQueue(Q, (*G)->adjList[i].data);
    while (Q->front != Q->rear) {
        char VertexNode = DeQueue(Q);
        printf("%c", VertexNode);
        struct EdgeNode *p = (*G)->adjList[i].firstEdge;
        while (p)
        {
            if (!visitedBFS[p->adjvex]) {
                visitedBFS[p->adjvex] = 1;
                EnQueue(Q, (*G)->adjList[p->adjvex].data);
            }
            p = p->next;  //指向与该节点相邻的下一条边
        }
    }
}

void BFSTravers(struct Graph **G) {
    struct Queue *qhead = (struct Queue *)malloc(sizeof(struct Queue));
    InitQueue(qhead);
    for (int i = 0; i < (*G)->numVertex; i++) {
        visitedBFS[i] = 1;
        if (!visitedBFS[i]) {  //判断节点是否访问
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