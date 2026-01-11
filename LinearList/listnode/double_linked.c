#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node {
    ElemType data;
    struct Node* prev;
    struct Node* next;
}DNode;

DNode* initList() {
    DNode* head = (DNode*)malloc(sizeof(DNode));
    if (head == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    head->data = 0;
    head->prev = NULL;
    head->next = NULL;
    return head;
}


void insertHead(DNode* head, ElemType e) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = e;

    newNode->prev = head;
    newNode->next = head->next;
    if (head->next != NULL) {
        head->next->prev = newNode;
    }
    head->next = newNode;
}

// 获取尾节点 传入头节点
DNode* getLast(DNode* L) {
    DNode* p = L;
    while (p->next != NULL) {
        p = p->next;
    }
    return p;
}

// 尾插法
DNode* insertLast(DNode* head, ElemType e) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = e;

    DNode* last = getLast(head);
    last->next = newNode;
    newNode->prev = last;
    newNode->next = NULL;
    return newNode;
}

// 指定位置插入 (头节点的位置是0)
// 传入参数：头节点，插入位置，插入数据
int insertPos(DNode* L, int pos, ElemType e) {
    int i = 0;
    DNode* current = L;
    // 找到待插入位置的前驱
    while (i < pos - 1) {
        current = current->next;
        i++;
        if (current == NULL) {
            return -1;
        }
    }
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    newNode->data = e;

    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;

    return 1;
}

// 指定位置删除节点
int deletePos(DNode* L, int pos) {
    int i = 0;
    DNode* current = L;
    // 找到待删除位置的前驱
    while (i < pos - 1) {
        current = current->next;
        i++;
        if (current == NULL) {
            return -1;
        }
    }
    
    DNode* temp = current->next;
    if (temp == NULL) {
        return -1;
    }

    if (temp->next != NULL) {
        temp->next->prev = current;
    }
    current->next = temp->next;
    free(temp);

    return 1;
}

// 打印链表内容
void printNode(DNode* head) {
    // 遍历链表输出节点的data
    DNode* temp = head->next;
    printf("Node data:");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 释放内存
void freeList(DNode* head) {
    DNode* current = head->next; // 当前节点
    DNode* temp = NULL; // 临时指针保存下一个节点
    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }
    head->next = NULL; // 重要：在释放完成后将头指针设置为NULL
    head->data = 0; // 释放完成后，节点数设置为0
}


int main(void) {

    DNode* head = initList();
    if (head == NULL) {
        return -1;
    }

    // 头插法
    insertHead(head, 10);
    insertHead(head, 20);
    insertHead(head, 30);

    printNode(head);

    // 尾插法
    insertLast(head, 40);
    insertLast(head, 50);

    printNode(head);

    // 指定位置插入
    insertPos(head, 2, 25);
    printNode(head);

    // 指定位置删除
    deletePos(head, 4);

    printNode(head);

    freeList(head);
    return 0;
}