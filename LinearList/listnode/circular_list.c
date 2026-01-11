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

// // 打印链表内容
// void printNode(LNode* head) {
//     // 遍历链表输出节点的data
//     printf("total nodes: %d\n", head->data);
//     LNode* temp = head->next;
//     printf("Node data:");
//     while (temp != NULL) {
//         printf("%d ", temp->data);
//         temp = temp->next;
//     }
//     printf("\n");
// }

// // 指定位置插入 (头节点的位置是0)
// // 传入参数：头节点，插入位置，插入数据
// int insertPos(LNode* L, int pos, ElemType e) {
//     LNode* prior = L; // 用来保存待插入节点的前驱节点
//     int i = 0;
//     while (i < pos - 1) {
//         prior = prior->next;
//         i++;
//         if (prior == NULL) return 0;
//     }
//     LNode* newNode = (LNode*)malloc(sizeof(LNode));
//     newNode->data = e;

//     newNode->next = prior->next;
//     prior->next = newNode;

//     L->data++;
//     return 1;
// }

// 判断链表是否有环
int isCycle(LNode* head) {
    LNode* Fast = head;
    LNode* Slow = head;
    while (Fast != NULL && Fast->next != NULL) {
        Fast = Fast->next->next;
        Slow = Slow->next;
        if (Fast == Slow) {
            return 1;
        }
    }
    return 0;
}

// 找到环的入口
LNode* findEntrance(LNode* head) {
    if (head == NULL || head->next == NULL) return NULL;
    LNode* fast = head;
    LNode* slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) break;
    }
    if (fast == NULL || fast->next == NULL) return NULL;
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// 释放内存 （循环链表）
void freeList(LNode* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    LNode* current = head->next; // 当前节点
    LNode* entrance = findEntrance(head);
    LNode* temp = NULL; // 临时指针保存下一个节点
    while (current != NULL && current != entrance) {
        temp = current->next;
        free(current);
        current = temp;
    }
    if (entrance != NULL) {
        current = entrance->next;
        while (current != NULL && current != entrance) {
            temp = current->next;
            free(current);
            current = temp;
        }
    }
    free(entrance);
    head->next = NULL; // 重要：在释放完成后将头指针设置为NULL
    head->data = 0; // 释放完成后，节点数设置为0
}

int main() {
    
    LNode* head = initList();
    LNode* last = getLast(head);

    // 构造循环链表
    last = insertLast(head, 1);
    last = insertLast(head, 2);
    last = insertLast(head, 3);
    LNode* three = last;
    last = insertLast(head, 4);
    last = insertLast(head, 5);
    last = insertLast(head, 6);
    last = insertLast(head, 7);
    last = insertLast(head, 8);
    last->next = three;



    if(isCycle(head)) {
        printf("有环\n");
    }
    else {
        printf("无环\n");
    }
    LNode* Entrance = findEntrance(head);
    printf("入口在节点%d\n", Entrance->data);
    
    freeList(head);
    
    return 0;
}