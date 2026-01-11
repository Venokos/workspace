#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
    ElemType data;
    struct node* next;
}LNode, *Linklist;
// LNode是一个节点对象，Linklist是一个指针


LNode* initList() {
    LNode* head = (Linklist)malloc(sizeof(LNode));
    if (head == NULL) {
        printf("开辟节点失败！\n");
        exit(1);
    }
    head->data = 0; // 记录链表节点数
    head->next = NULL;
    return head;
}

// 获取尾节点 传入头节点
LNode* getLast(LNode* L) {
    LNode* p = L;
    while (p->next != NULL) {
        p = p->next;
    }
    return p;
}

// 尾插法
LNode* insertLast(LNode* head, ElemType e) {
    LNode* newnode; // newnode是一个指向新节点的指针
    newnode = (LNode *)malloc(sizeof(LNode));
    newnode->data = e;
    newnode->next = NULL;

    LNode* lastnode = getLast(head); // 获取当前链表最后一个节点
    lastnode->next = newnode; // 插入前的最后一个节点 指向新节点
    
    head->data++; // 节点个数+1
    
    return newnode;
}

// 打印链表内容
void printNode(LNode* head) {
    // 遍历链表输出节点的data
    printf("total nodes: %d\n", head->data);
    LNode* temp = head->next;
    printf("Node data:");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 删除中间节点（快慢指针）
void delete_mid(LNode* head) {
    LNode* fast = head->next;
    LNode* slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    LNode* temp = slow->next;
    slow->next = temp->next;
    free(temp);
}



// 释放内存
void freeList(LNode* head) {
    LNode* current = head->next; // 当前节点
    LNode* temp = NULL; // 临时指针保存下一个节点
    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }
    head->next = NULL; // 重要：在释放完成后将头指针设置为NULL
    head->data = 0; // 释放完成后，节点数设置为0
}

int main() {
    
    LNode* head = initList();
    LNode* last = getLast(head);

    last = insertLast(head, 21);
    last = insertLast(head, -15);
    last = insertLast(head, 9);
    last = insertLast(head, -7);
    last = insertLast(head, 1);
    last = insertLast(head, 99);
    printNode(head);

    delete_mid(head);
    printNode(head);
    
    freeList(head);
    free(head);
    
    return 0;
}