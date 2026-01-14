#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;

#define MAX_SIZE 100

typedef struct {
    Elemtype data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

int isFull(Queue *q) {
    return (q->front == 0 && q->rear == MAX_SIZE);
}

// 出队
int deQueue(Queue* q, Elemtype* e) {
    if (isEmpty(q)) {
        printf("The queue is empty.\n");
        return -1;
    }

    *e = q->data[q->front];
    q->front++;
    return 0;
}

// 移动队列元素到队头
void moveToFront(Queue* q) {
    if (isEmpty(q)) {
        printf("The queue is empty.\n");
        return;
    }

    int step = q->front;
    for (int i = 0; i < step; i++) {
        q->data[i] = q->data[q->front + i]; 
    }

    q->front = 0;
    q->rear = step;
}

// 入队
int enQueue(Queue* q, Elemtype e) {
    if (isFull(q)) {
        printf("The queue is full.\n");
        return -1;
    }
    else {
        if (q->rear >= MAX_SIZE) {
            moveToFront(q);
            enQueue(q, e);
        }
        else {
            q->data[q->rear] = e;
            q->rear++;
        }
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


int main() {

    Queue q;
    initQueue(&q);

    enQueue(&q, 10);
    enQueue(&q, 20);
    enQueue(&q, 40);

    Elemtype e1, e2, e3, e4, e5;;
    deQueue(&q, &e1);
    deQueue(&q, &e2);
    getFront(&q, &e3);

    enQueue(&q, 30);
    deQueue(&q, &e4);
    deQueue(&q, &e5);
    printf("%d %d %d %d %d\n", e1, e2, e3, e4, e5);

    deQueue(&q, &e5);


    return 0;
}