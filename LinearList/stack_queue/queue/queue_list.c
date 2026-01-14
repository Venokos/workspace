#include <stdio.h>
#include <stdlib.h>

// 学校作业，不带头节点的链表方式实现队列


// 链表结构体
typedef struct QNode {
    int data;
    struct QNode* next;
}QueueNode;
// 队列结构体
typedef struct {
    QueueNode* front; // 队头
    QueueNode* rear; // 队尾
    int size; // 队列当前元素个数
}LinkedQueue;

// 初始化队列
void initQueue(LinkedQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}
// 判断队列是否为空
int isEmpty(LinkedQueue* queue) {
    return queue->front == NULL;
}
// 将值value入队
int EnQueue(LinkedQueue* queue, int value) {
    QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newnode == NULL) return 0; // 内存分配失败
    newnode->data = value;
    newnode->next = NULL;
    // 如果队列为空
    if (isEmpty(queue)) {
        queue->front = newnode;
        queue->rear = newnode;
    }
    // 如果队列不为空
    else {
        queue->rear->next = newnode; // 新节点链接到队尾
        queue->rear = newnode; // 更新队尾指针
    }
    queue->size++; // 队列元素个数+1
    return 1; // 入队成功
}
// 出队：从队头移除元素, value记录该次出队元素
int DeQueue(LinkedQueue* queue, int* value) {
    if (isEmpty(queue)) return 0; // 队列为空，无法出队

    QueueNode* temp = queue->front;
    if (value != NULL) {
        *value = temp->data;
    }
    // 如果队列只有一个元素，出队后队列为空
    if (queue->front == queue->rear) {
        queue->front = NULL;
        queue->rear = NULL;
    }
    // 如果队列元素大于1
    else {
        queue->front = queue->front->next;
    }
    free(temp); // 释放待出列节点
    queue->size--; // 队列元素个数-1
    return 1; // 出队成功
}

// 打印队列元素
void printQueue(LinkedQueue* queue) {
    if (isEmpty(queue)) return;
    QueueNode* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
// 释放内存
void freeQueue(LinkedQueue* queue) {
    while (!isEmpty(queue)) {
        int temp;
        DeQueue(queue, &temp);
    }
    
}

int main() {
    LinkedQueue queue;
    initQueue(&queue);
    // 入队
    EnQueue(&queue, 10);
    EnQueue(&queue, 20);
    EnQueue(&queue, 30);
    EnQueue(&queue, 40);
    printQueue(&queue);
    // 出队
    int value;
    while (!isEmpty(&queue)) {
        DeQueue(&queue, &value);
        printf("出队元素:%d \n", value);
        printQueue(&queue);
    }




    return 0;
}