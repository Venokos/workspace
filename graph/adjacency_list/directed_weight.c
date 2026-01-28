#include <stdio.h>
#include <stdlib.h>

// 程序：带权值有向图邻接表

#define MAXVEX 100 // 最大顶点数
typedef char VertexType; // 顶点数据类型(V0, V1, V2, V3)
typedef int EdgeType; // 边权值数据类型（表示所连接的顶点的下标）

// 边结点结构体
typedef struct EdgeNode {
    EdgeType adjvex; // 理解为边结点的data，存储的是所连接的顶点的下标，比如adjvex为0表示与V0连接
    int weight;
    struct EdgeNode* next;
} EdgeNode;

// 顶点结点结构体
typedef struct {
    VertexType data; // 顶点名称(V0, V1, V2, V3)
    EdgeNode* firstedge; // 顶点结点所指向的第一个边结点，可理解为顶点结点的next 
    // 拿到了顶点结点就可以拿到一整条链表
} VertexNode, arrVertex[MAXVEX];

// 图结构体定义
typedef struct {
    // vertex是一个数组，用于存储V0, V1, V2, V3等顶点结点 拿到这个数组就可以拿到多条链表组成的邻接表
    arrVertex vertex; // 邻接表，等价于 VertexNode vertex[MAXVEX];
    int vertex_num; // 顶点数
    int edge_num; // 边条数
} Graph;

// 初始化图
void createGraph (Graph* G) {
    // 四个顶点，五条边
    G->vertex_num = 4;
    G->edge_num = 5;
    // 顶点结点初始化
    for (int i = 0; i < G->vertex_num; i++) {
        G->vertex[i].data = '0' + i;
        G->vertex[i].firstedge = NULL;
    }
    // 边集合
    int edges[5][3] = {
        {0, 3, 30},
        {1, 0, 50},
        {1, 2, 20},
        {2, 0, 60}, 
        {2, 1, 40}
    };

    // 链表“头插法”
    for (int i = 0; i < G->edge_num; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        int weight = edges[i][2];

        // from->to
        EdgeNode* e1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        if (e1 == NULL) {
            printf("Memory Allocation Failed.\n");
            return;
        }
        e1->weight = weight;
        e1->adjvex = to; // e1->data = to;
        e1->next = G->vertex[from].firstedge; // to->next = Vfrom->next;
        G->vertex[from].firstedge = e1; // Vfrom->next = to;
    }
}

// 打印邻接表
void printGraph(Graph* G) {
    for (int i = 0; i < G->vertex_num; i++) {
        printf("V%c -> ", G->vertex[i].data);
        EdgeNode* curr = G->vertex[i].firstedge;
        while (curr) {
            printf(" %d[%d] ->", curr->adjvex, curr->weight);
            curr = curr->next;
        }
        printf(" ^\n");
    }
}


int main() {
    Graph G;
    createGraph(&G);
    printGraph(&G);

    return 0;
}