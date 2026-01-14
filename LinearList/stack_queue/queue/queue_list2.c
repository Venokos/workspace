#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;


// 节点结构体
typedef struct QueueNode {
    Elemtype data;
    struct QueueNode* next;
} QueueNode;

// 队列结构体
typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// 初始化
Queue* initQueue() {
    // 初始化队列
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    // 初始化头节点
    QueueNode* head = (QueueNode*)malloc(sizeof(QueueNode));
    if (head == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    
    head->data = 0;
    head->next = NULL;

    q->front = head;
    q->rear = head;

    return q;
}

// 判空
int isEmpty(Queue *q) {
    return q->front == q->rear;
}

// 入队（尾插法）
int enQueue(Queue* q, Elemtype e) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    newNode->data = e;
    newNode->next = NULL;

    q->rear->next = newNode;
    q->rear = newNode;

    return 0;
}

// 出队（删除头节点的下一个元素）
int deQueue(Queue* q, Elemtype* e) {
    if (isEmpty(q)) {
        printf("The queue is empty.\n");
        return -1;
    }

    QueueNode* temp = q->front->next;
    if (temp == q->rear) {
        q->rear = q->front;
        q->front->next = NULL;
    }
    else {
        q->front->next = temp->next;
    }

    *e = temp->data;

    free(temp);
    
    return 0;
}

// 获取队头元素
int getFront(Queue* q, Elemtype* e) {
    if (isEmpty(q)) {
        printf("The queue is empty.\n");
        return -1;
    }

    *e = q->front->next->data;

    return 0;
}

// 释放内存
void freeQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        int temp;
        deQueue(queue, &temp);
    }
    free(queue->front);
    free(queue);
}

int main() {

    Queue* q = initQueue();

    enQueue(q, 10);
    enQueue(q, 20);
    enQueue(q, 40);

    Elemtype e1, e2, e3, e4, e5;;
    deQueue(q, &e1);
    deQueue(q, &e2);
    getFront(q, &e3);

    enQueue(q, 30);
    deQueue(q, &e4);
    deQueue(q, &e5);
    printf("%d %d %d %d %d\n", e1, e2, e3, e4, e5);

    deQueue(q, &e5);
    getFront(q, &e3);


    freeQueue(q);
    return 0;
}