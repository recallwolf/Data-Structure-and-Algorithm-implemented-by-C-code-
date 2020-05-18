#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct Node {
    char data;
    struct Node *lchild;
    struct Node *rchild;
};

struct Queue {
    int front, rear;
    struct Node * data[100]; //存放树节点指针的数组
};


//初始化队列
void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = 0; 
}


//入队操作
void EnQueue(struct Queue *q, struct Node *pointer) {
    //printf("%d\n", q->rear);
    if (q->rear == 99) {
        printf("error");
    }
    else {
        q->data[(q->rear)++] = pointer;
    }   
}

//出队操作
struct Node *DeQueue(struct Queue *q) {
    return q->data[(q->front)++];
}


//层序遍历
void LevelOrderTraverse(struct Queue *q, struct Node *pointer) {
    initQueue(q); //初始化队列
    if (pointer) {
        EnQueue(q,pointer);
    }
    while (q->front != q->rear) {  //判断队列是否为空，不为空则出队
        struct Node *QueueEle = DeQueue(q);
        printf("%c", QueueEle->data);
        if (QueueEle -> lchild) {
            EnQueue(q,QueueEle->lchild); //入队左子节点
        }
        if (QueueEle -> rchild) {
            EnQueue(q,QueueEle->rchild); //入队右子节点
        }
    }
}

//对需要成树的数组进行处理，保证每次递归提取一个数组元素
int i = 0;
char initArray(char arr[]) {
    int length = strlen(arr);
    if (i < length) {
        return arr[i++];
    }
    else {
        return ' ';
    }
}

void CreateTree(struct Node **pointer) {  //二级指针 **pointer指向head指针的地址,故只需操作函数内*pointer即可改变外部head指针
    char arr[] = "12#46###3#5##";
    char ch = initArray(arr);
    //如果需要手动输入，可替换下列代码
    /*char ch;
    scanf("%c",&ch);*/
    if (ch == '#') *pointer = NULL;  //叶节点
    else{
        // 分配空间
        *pointer = (struct Node *)malloc(sizeof(struct Node));
        (*pointer) -> data = ch;
        CreateTree(&(*pointer)->lchild); //->优先级高于&
        CreateTree(&(*pointer)->rchild);
    }
}

//第二种建树方式，不需传参，故不需使用二级指针，、返回值为结构体指针
/*struct Node * CreateTree(){
    char arr[] = "12#46###3#5##";
    char ch = initArray(arr);
    struct Node *pointer;
    if(ch == '#') pointer = NULL;
    else{
        pointer = (struct Node *)malloc(sizeof(struct Node));
        pointer->data = ch;
        pointer->lchild = CreateTree();
        pointer->rchild = CreateTree();
    }
    return pointer;
}*/

//先序遍历 根左右
void PreOrderTravel(struct Node *pointer)
{
    if (pointer){
    printf("%c",pointer->data);
    if (pointer->lchild) PreOrderTravel(pointer->lchild);
    if (pointer->rchild) PreOrderTravel(pointer->rchild);
    }
}

//中序遍历 左根右
void InorderTraverser(struct Node *pointer){
    if (pointer){
        if (pointer->lchild) InorderTraverser(pointer->lchild);
        printf("%c", pointer->data);
        if (pointer->rchild) InorderTraverser(pointer->rchild);
    }
}

//后序遍历 左右根
void PostOrderTraverse(struct Node *pointer){
    if (pointer){
        if (pointer->lchild)  PostOrderTraverse(pointer->lchild);
        if (pointer->rchild)  PostOrderTraverse(pointer->rchild);
        printf("%c", pointer->data);
    }
}

void main() {
    struct Node *head; //创建根节点，指针指向结构体地址
    struct Queue *qhead = (struct Queue *)malloc(sizeof(struct Queue));
    CreateTree(&head); //建树，传递指针head的地址,等价于struct Node **p = &head
    //head = CreateTree(); //第二种建树方式，不采用二级指针，直接返回结构体指针

    printf("先序遍历结果：\n");
    PreOrderTravel(head);
    printf("\n");
    printf("中序遍历结果：\n");
    InorderTraverser(head);
    printf("\n");
    printf("后序遍历结果：\n");
    PostOrderTraverse(head);
    printf("\n");
    printf("层序遍历结果：\n");
    LevelOrderTraverse(qhead,head);
}