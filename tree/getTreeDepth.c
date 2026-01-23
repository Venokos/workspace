#include <stdio.h>
#include <stdlib.h>

// 程序：获取二叉树的深度


// 队列最大元素数量
#define MAX_SIZE 100

// 树结点存储的数据类型
typedef char TreeNodeType;

// 树结点结构体
typedef struct TreeNode {
    TreeNodeType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
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

char data[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;

// 利用前序遍历创建树
BiTree createTree() {

    char ch = data[idx++];

    if (ch == '#') {
        return NULL;
    }
    
    BiTree T = (BiTree)malloc(sizeof(TreeNode));
    if (T == NULL) {
        printf("Memory Allocation Failed.\n");
        return NULL;
    }

    T->data = ch; 
    T->lchild = createTree();   
    T->rchild = createTree(); 

    return T;
}

// 求二叉树的高度
int getTreeDepth(BiTree T) {
    // 如果传入空树
    if (T == NULL) {
        return 0;
    }

    // 创建一个队列
    Queue* q = initQueue();
    // 将根结点入队
    enQueue(q, T);

    int depth = 0;
    // 外层循环退出条件：队列为空
    while (!isEmpty(q)) {
        int count = getQueueSize(q); // 获取当前队列长度，也是该层结点个数
        // 对该层的每个结点：该结点出队，该结点的左右孩子入队
        while (count > 0) {
            TreeNode* curr = NULL;
            deQueue(q, &curr);
            // 如果有左孩子，则左孩子入队
            if (curr->lchild) {
                enQueue(q, curr->lchild);
            }
            // 如果有右孩子，则右孩子入队
            if (curr->rchild) {
                enQueue(q, curr->rchild);
            }
            count--;
        }
        depth++;
    }
    // 外层循环退出，代表最后一层的所有结点都没有孩子入队了（也就是该层都是叶子节点）

    free(q); // 释放队列内存
    return depth;
}


// 释放树内存
void freeTree(BiTree T) {
    if (T != NULL) {
        freeTree(T->lchild);
        freeTree(T->rchild);
        free(T);
    }
}

int main() {

    BiTree T = createTree();
    printf("Depth of this tree: %d\n", getTreeDepth(T));

    freeTree(T);
    
    
    return 0;
}