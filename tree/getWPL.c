#include <stdio.h>
#include <stdlib.h>

// 程序：给定二叉树T 以及 指向该二叉树根结点的指针root，
// 采用二叉链表存储，结点结构：left weight right，weight表示该结点非负权重，
// 计算该二叉树的WPL (带权路径长度)。

// 需解决：1.判断叶子结点（左右孩子均为空） 
// 2.计算叶子结点路径长度（利用求二叉树深度的程序:如果根结点的深度为1,则结点路径长度 = 深度 - 1）


// 队列最大元素数量
#define MAX_SIZE 100

// 树结点存储的数据类型
typedef int TreeNodeType;

// 树结点结构体
typedef struct TreeNode {
    TreeNodeType weight;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef TreeNode* BiTree;

// 队列中存储的数据类型
typedef TreeNode* ElemType;

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

    q->data = (ElemType*)malloc(sizeof(ElemType) * MAX_SIZE);
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
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// 出队
int deQueue(Queue* q, ElemType* e) {
    if (isEmpty(q)) {
        printf("The queue is empty.\n");
        return -1;
    }

    *e = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
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
        q->rear = (q->rear + 1) % MAX_SIZE;
        return 0;
    }
}

// 获取队列长度
int getQueueSize(Queue* q) {
    return (q->rear - q->front + MAX_SIZE) % MAX_SIZE;
}

// 记录结点权重的数组，100表示根结点，-1表示空
TreeNodeType data[] = {100, 42, 15, -1, -1, 27, -1, -1, 
                58, 28, 13, 5, -1, -1, 8, -1, -1,
                15, -1, -1, 30, -1, -1};
int idx = 0;

// 利用前序遍历创建树
BiTree createTree() {

    TreeNodeType ch = data[idx++];

    if (ch == -1) {
        return NULL;
    }
    
    BiTree T = (BiTree)malloc(sizeof(TreeNode));
    if (T == NULL) {
        printf("Memory Allocation Failed.\n");
        return NULL;
    }

    T->weight = ch; 
    T->left = createTree();   
    T->right = createTree(); 

    return T;
}

// 按照题意计算wpl
int wpl(BiTree T) {
    // 如果传入空树
    if (T == NULL) {
        return 0;
    }

    // 创建一个队列
    Queue* q = initQueue();
    // 将根结点入队
    enQueue(q, T);

    int depth = 0;
    int wpl = 0;

    TreeNode* curr = NULL;

    // 外层循环退出条件：队列为空
    while (!isEmpty(q)) {
        int count = getQueueSize(q); // 获取当前队列长度，也是该层结点个数
        // 对该层的每个结点：该结点出队，该结点的左右孩子入队
        while (count > 0) {
            deQueue(q, &curr);
            // 如果有左孩子，则左孩子入队
            if (curr->left) {
                enQueue(q, curr->left);
            }
            // 如果有右孩子，则右孩子入队
            if (curr->right) {
                enQueue(q, curr->right);
            }
            // 如果该节点为叶子节点，则计算wpl
            if (curr->left == NULL && curr->right == NULL) {
                wpl += curr->weight * depth;
            }
            count--;
        }
        depth++;
    }

    free(q); // 释放队列内存
    return wpl;
}


// 释放树内存
void freeTree(BiTree T) {
    if (T != NULL) {
        freeTree(T->left);
        freeTree(T->right);
        free(T);
    }
}

int main() {

    BiTree root = createTree();
    printf("WPL of this tree: %d\n", wpl(root));

    freeTree(root);
    
    return 0;
}