#include <stdio.h>
#include <stdlib.h>

// 程序：有向图带权值邻接矩阵

#define MAXSIZE 100 // 最大顶点数
#define MAX 0x7fffffff // int能表示的最大值(2^31-1，用来表达无穷大)
typedef char VertexType; // 顶点数据类型
typedef int EdgeType; // 边权值数据类型（对角线用0表示，无连接用无穷大MAX表示，其余用权值表示）

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
            G->arc[i][j] = MAX;
            if (i == j) {
                G->arc[i][j] = 0;
            }
        }
    }
    
    G->arc[0][3] = 3; // V0->V3 权为3
    G->arc[1][0] = 5; // V1->V0 权为5
    G->arc[1][2] = 2; // V1->V2 权为2
    G->arc[2][0] = 6; // V2->V0 权为6
    G->arc[2][1] = 4; // V2->V1 权为4
    
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
            if (G->arc[i][j] == MAX) {
                printf("∞\t");
            }
            else {
                printf("%d\t", G->arc[i][j]);
            } 
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