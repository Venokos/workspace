#include <stdio.h>
#include <stdlib.h>

// 程序：有向图邻接矩阵

#define MAXSIZE 100 // 最大顶点数
typedef char VertexType; // 顶点数据类型
typedef int EdgeType; // 边权值数据类型（0表示无连接，1表示有连接）

// 图的邻接矩阵结构体
typedef struct {
    VertexType vertex[MAXSIZE]; // 顶点数组
    EdgeType arc[MAXSIZE][MAXSIZE]; // 邻接矩阵
    int vertexNum; // 顶点个数
    int edgeNum; // 边的条数
} graphMatrix;

// 创建邻接矩阵
void create_graph(graphMatrix* G) {
    // 四个顶点，五条边
    G->vertexNum = 4;
    G->edgeNum = 5;
    // 顶点名字 (V0, V1, V2, V3)
    for (int i = 0; i < G->vertexNum; i++) {
        G->vertex[i] = '0' + i;
    }
    // 初始化矩阵元素
    for (int i = 0; i < G->vertexNum; i++) {
        for (int j = 0; j < G->vertexNum; j++) {
            G->arc[i][j] = 0;
        }
    }
    
    G->arc[0][3] = 1; // V0->V3
    G->arc[1][0] = 1; // V1->V0
    G->arc[1][2] = 1; // V1->V2
    G->arc[2][0] = 1; // V2->V0
    G->arc[2][1] = 1; // V2->V1
    
}

// 输出邻接矩阵
void printMatrix(graphMatrix* G) {
    for (int i = 0; i < G->vertexNum; i++) {
        printf("\tV%c", G->vertex[i]);
    }
    printf("\n");
    for (int i = 0; i < G->vertexNum; i++) {
        printf("V%c\t", G->vertex[i]);
        for (int j = 0; j < G->vertexNum; j++) {
            printf("%d\t", G->arc[i][j]);
        }
        printf("\n");
    }
}


int main() {
    graphMatrix G;
    create_graph(&G);
    printMatrix(&G);

    return 0;
}