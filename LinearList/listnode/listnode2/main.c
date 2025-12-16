#include <stdio.h>
#include <stdlib.h>

struct LNode {
    int data;
    struct LNode* next;
};

struct LNode* head = NULL; // 全局头指针head

// 头插法
void insertHead(int e) {
    struct LNode* newnode;
    newnode = (struct LNode*)malloc(sizeof(struct LNode));
    newnode->data = e;
    newnode->next = head;
    head = newnode;
}
// 打印链表内容
void printNode() {
    // 遍历链表输出节点的data
    struct LNode* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}
// 释放内存
void freeList() {
    struct LNode* current = head; // 当前节点
    struct LNode* temp; // 临时指针保存下一个节点
    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }
    head = NULL; // 重要：在释放完成后将头指针设置为NULL
}

int main()
{
    insertHead(10);
    insertHead(20);
    insertHead(30);
    printNode();
    freeList();

    return 0;
}
