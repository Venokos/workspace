#include <stdio.h>
#include <stdlib.h>

// 不带头节点的单链表 2025.12.10


struct LNode {
    int data;
    struct LNode* next;
};

struct LNode* head = NULL;

void insertHead(int e) {
    struct LNode* newnode;
    newnode = (struct LNode*)malloc(sizeof(struct LNode));
    newnode->data = e;
    newnode->next = head;
    head = newnode;
}


int main()
{
    // 创建节点指针
    struct LNode *head, *middle, *last;
    // 为节点开辟内存，让节点指针指向他们的内存
    head = (struct LNode*)malloc(sizeof(struct LNode));
    middle = (struct LNode*)malloc(sizeof(struct LNode));
    last = (struct LNode*)malloc(sizeof(struct LNode));
    // 初始化节点data
    head->data = 10;
    middle->data = 20;
    last->data = 30;
    // 把节点连接起来
    head->next = middle;
    middle->next = last;
    last->next = NULL;
    // 遍历链表输出节点的data
    struct LNode* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    free(head);
    free(middle);
    free(last);

    return 0;
}
