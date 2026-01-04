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

// 指定位置插入 (头节点的位置是0)
// 传入参数：头节点，插入位置，插入数据
int insertPos(LNode* L, int pos, ElemType e) {
    LNode* prior = L; // 用来保存待插入节点的前驱节点
    int i = 0;
    while (i < pos - 1) {
        prior = prior->next;
        i++;
        if (prior == NULL) return 0;
    }
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    newNode->data = e;

    newNode->next = prior->next;
    prior->next = newNode;

    L->data++;
    return 1;
}

// 删除绝对值相同的节点，只保留第一个节点
// 传入参数：头节点，数组元素最大值（绝对值）
void deleteSame(LNode* L, int n) {
    int* found = (int*)malloc(sizeof(int) * (n + 1)); // 记录数字是否出现过的数组
    LNode* current = L;

    // 遍历数组，初始化值为0
    int* p = found;
    for (int i = 0; i < n + 1; i++, p++) {
        *p = 0;
    }

    while (current->next != NULL) {
        if (!found[abs(current->next->data)]) {
            found[abs(current->next->data)] = 1;
            current = current->next;
        }
        else {
            LNode* temp = current->next;
            current->next = temp->next;
            free(temp);
            L->data--;
        }
    }
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
    last = insertLast(head, -15);
    last = insertLast(head, -7);
    last = insertLast(head, 15);
    printNode(head);

    deleteSame(head, 21);
    printNode(head);

    
    freeList(head);
    
    return 0;
}