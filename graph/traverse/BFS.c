#include <stdio.h>
#include <stdlib.h>

// 程序：BFS（广度优先）算法实现


#define MAXSIZE 100


typedef int ElemType; // 队列中存储的数据类型

typedef char VertexType; // 顶点数据类型
typedef int EdgeType; // 边权值数据类型（0表示无连接，1表示有连接）

// 图的邻接矩阵结构体
typedef struct {
    VertexType vertex[MAXSIZE]; // 顶点数组
    EdgeType arc[MAXSIZE][MAXSIZE]; // 邻接矩阵
    int vertexNum; // 顶点个数
    int edgeNum; // 边的条数
} graphMatrix;

// 队列结构体
typedef struct {
    ElemType *data;
    int front;
    int rear;
} Queue;

// 初始化队列
Queue* initQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    q->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    if (q->data == NULL) {
        printf("Memory allocation failed.\n");
        free(q);
        return NULL;
    }
    
    q->front = 0;
    q->rear = 0;
    
    return q;
}

// 队列判空
int isEmpty(Queue *q) {
    return q->front == q->rear;
}

// 队列判满
int isFull(Queue *q) {
    return (q->rear + 1) % MAXSIZE == q->front;
}

// 出队
int deQueue(Queue* q, ElemType* e) {
    if (isEmpty(q)) {
        printf("The queue is empty.\n");
        return -1;
    }

    *e = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return 0;
}

// 入队
int enQueue(Queue* q, ElemType e) {
    if (isFull(q)) {
        printf("The queue is full.\n");
        return -1;
    }
    else {
        q->data[q->rear] = e;
        q->rear = (q->rear + 1) % MAXSIZE;
        return 0;
    }
}

// 创建邻接矩阵
void create_graph(graphMatrix* G) {
    // 9个顶点，15条边
    G->vertexNum = 9;
    G->edgeNum = 15;
    // 顶点名字 (A~I)
    for (int i = 0; i < G->vertexNum; i++) {
        G->vertex[i] = 'A' + i;
    }
    // 初始化矩阵元素
    for (int i = 0; i < G->vertexNum; i++) {
        for (int j = 0; j < G->vertexNum; j++) {
            G->arc[i][j] = 0;
        }
    }
    // A-B, A-F
    G->arc[0][1] = 1, G->arc[0][5] = 1;
    // B-C, B-G, B-I
    G->arc[1][2] = 1, G->arc[1][6] = 1, G->arc[1][8] = 1;
    // C-D, C-I
    G->arc[2][3] = 1, G->arc[2][8] = 1;
    // D-E, D-G, D-H, D-I
    G->arc[3][4] = 1, G->arc[3][6] = 1, G->arc[3][7] = 1, G->arc[3][8] = 1;
    // E-F, E-H
    G->arc[4][5] = 1, G->arc[4][7] = 1;
    // F-G, G-H
    G->arc[5][6] = 1, G->arc[6][7] = 1;
    // 无向图的邻接矩阵是对称矩阵 a[i][j] = a[j][i]
    for (int i = 0; i < G->vertexNum; i++) {
        for (int j = i; j < G->vertexNum; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

// 广度优先遍历算法实现（类似层序遍历）
void bfs(graphMatrix* G) {
    // visited数组判断结点是否被访问过
    static int visited[MAXSIZE] = {0};

    // 创建一个队列
    Queue* q = initQueue();

    // 先输出结点0并入队
    int i = 0;
    visited[i] = 1;
    printf("%c ", G->vertex[i]);
    enQueue(q, i);

    // 外层循环退出条件：队列为空
    while (!isEmpty(q)) {
        deQueue(q, &i); // 队头结点出队，存储在i中
        // 对每个结点，判断是否为结点i的孩子且未被访问过
        for (int j = 0; j < G->vertexNum; j++) {   
            // 如果是结点i的孩子，且未被访问过，则标记访问过并输出，同时将该结点入队
            if (G->arc[i][j] && !visited[j]) {
                visited[j] = 1;
                printf("%c ", G->vertex[j]);
                enQueue(q, j);
            }
        }
    }
    free(q); // 释放队列内存
}



int main() {
    graphMatrix G;
    create_graph(&G);

    printf("广度优先遍历结果如下:\n");
    bfs(&G);
    printf("\n");
    
    return 0;
}