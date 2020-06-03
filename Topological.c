#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct VertexNode {
    char data;
    int count;  //入度
    struct EdgeNode *firstEdge; 
};

struct EdgeNode {
    int adjvex;
    int weight;
    struct EdgeNode *next;
};

struct Graph {
    struct VertexNode adjList[10];
    int numVertex, numEdge;
};

void createGraph(struct Graph **G, char arr[]) {
    *G = (struct Graph *)malloc(sizeof(struct Graph));
    (*G) -> numVertex = strlen(arr);
    for (int i = 0; i < (*G) -> numVertex; i++) {
        (*G) -> adjList[i].data = arr[i];
    }
    int edge[][3] = {
        {0, 1, 0}, 
        {0, 2, 0}, 
        {0, 3, 0}, 
        {1, 4, 1}, 
        {2, 4, 1}, 
        {3, 4, 1}
    };
    (*G) -> numEdge =   (sizeof(edge) / sizeof(int)/3);

    for(int i = 0; i < (*G) -> numEdge; i++) {
        (*G)->adjList[i].firstEdge = NULL;
        struct EdgeNode *e = (struct EdgeNode *)malloc(sizeof(struct EdgeNode));
        e -> adjvex = edge[i][1];
        e -> next = (*G) -> adjList[edge[i][0]].firstEdge;
        (*G) -> adjList[edge[i][0]].count = edge[i][2];
        (*G) -> adjList[edge[i][0]].firstEdge = e;
    }
    (*G) -> adjList[(*G) -> numVertex - 1].count = 3;
}

int TopologicalSort(struct Graph *G) {
    int i, j;
    int array[100], top = -1, n = 0;
    struct EdgeNode *edge;
    for (int i = 0; i < G -> numVertex; i++) {
        if (G -> adjList[i].count == 0) {
            // 找到入度为0的结点，存入数组
            array[++top] = i;
        }
    }
    while (top != -1) {
        i = array[top--];
        n++;
        printf("%d", i);
        edge = G ->adjList[i].firstEdge;
        while (edge != NULL) {
            j = edge -> adjvex;
            // 减少了1条边，相应结点入度减1
            G ->adjList[j].count--;
            if (G ->adjList[j].count == 0) {
                //如果当前入度为0，则取出放入数组
                array[++top] = j;
            }
            edge = edge->next;
        }
    }
    if(n==G->numVertex) return 1;
    else return 0;

}

// DFS
int visitedNode[100];
void InverseTopologicalSort(int i, struct Graph *G) {
    visitedNode[i] = 1;
    struct EdgeNode *edge = G->adjList[i].firstEdge;
    while(edge != NULL) {
        if(visitedNode[edge->adjvex] == 0) {
            InverseTopologicalSort(edge->adjvex, G);
        }
        edge = edge->next;
    }
    printf("%d", i);
}

void main() {
    struct Graph *G;
    char VertexNode[] = "ABCDE";
    createGraph(&G, VertexNode);
    TopologicalSort(G);
    printf("\n");
    InverseTopologicalSort(0, G);
}