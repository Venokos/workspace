#include <stdio.h>
#include <stdlib.h>

// 动态内存分配，建立循环队列

typedef int Elemtype;

#define MAX_SIZE 100

typedef struct {
    Elemtype *data;
    int front;
    int rear;
} Queue;

Queue* initQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    q->data = (Elemtype*)malloc(sizeof(Elemtype) * MAX_SIZE);
    if (q->data == NULL) {
        printf("Memory allocation failed.\n");
        free(q);
        return NULL;
    }
    
    q->front = 0;
    q->rear = 0;
    
    return q;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

int isFull(Queue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// 出队
int deQueue(Queue* q, Elemtype* e) {
    if (isEmpty(q)) {
        printf("The queue is empty.\n");
        return -1;
    }

    *e = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return 0;
}



// 入队
int enQueue(Queue* q, Elemtype e) {
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

// 获取队头元素
int getFront(Queue* q, Elemtype* e) {
    if (isEmpty(q)) {
        printf("The queue is empty.\n");
        return -1;
    }

    *e = q->data[q->front];
    return 0;
}

// 获取队列长度
int getQueueSize(Queue* q) {
    return (q->rear - q->front + MAX_SIZE) % MAX_SIZE;
}

// 释放内存
void freeQueue(Queue* queue) {
    free(queue->data);
    free(queue);
}

int main() {

    Queue* q = initQueue();

    enQueue(q, 10);
    printf("Queue size: %d\n", getQueueSize(q));
    enQueue(q, 20);
    printf("Queue size: %d\n", getQueueSize(q));
    enQueue(q, 40);
    printf("Queue size: %d\n", getQueueSize(q));

    Elemtype e1, e2, e3, e4, e5;;
    deQueue(q, &e1);
    printf("Queue size: %d\n", getQueueSize(q));
    deQueue(q, &e2);
    printf("Queue size: %d\n", getQueueSize(q));
    getFront(q, &e3);

    enQueue(q, 30);
    printf("Queue size: %d\n", getQueueSize(q));
    deQueue(q, &e4);
    printf("Queue size: %d\n", getQueueSize(q));
    deQueue(q, &e5);
    printf("Queue size: %d\n", getQueueSize(q));
    printf("%d %d %d %d %d\n", e1, e2, e3, e4, e5);

    deQueue(q, &e5);
    printf("Queue size: %d\n", getQueueSize(q));

    freeQueue(q);

    return 0;
}