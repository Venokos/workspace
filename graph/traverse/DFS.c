#include <stdio.h>
#include <stdlib.h>

// 程序：深度优先（DFS）算法实现

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

// 深度优先算法 传入图和顶点下标
void dfs(graphMatrix* G, int i) {
    // visited数组判断结点是否被访问过
    static int visited[MAXSIZE] = {0};
    // 访问并输出结点i
    visited[i] = 1;
    printf("%c ", G->vertex[i]);
    // 对于结点i，遍历所有结点j，如果i与j有连接且j未被访问过，则递归调用结点j
    for (int j = 0; j < G->vertexNum; j++) {
        if (G->arc[i][j] && !visited[j]) {
            dfs(G, j);
        }
    }
}

// 输出邻接矩阵
void printMatrix(graphMatrix* G) {
    for (int i = 0; i < G->vertexNum; i++) {
        printf("\t%c", G->vertex[i]);
    }
    printf("\n");
    for (int i = 0; i < G->vertexNum; i++) {
        printf("%c\t", G->vertex[i]);
        for (int j = 0; j < G->vertexNum; j++) {
            printf("%d\t", G->arc[i][j]);
        }
        printf("\n");
    }
}


int main() {
    graphMatrix G;
    create_graph(&G);
    printf("邻接矩阵如下:\n");
    printMatrix(&G);
    printf("\n");

    printf("深度优先遍历结果如下:\n");
    dfs(&G, 0);
    printf("\n");

    return 0;
}