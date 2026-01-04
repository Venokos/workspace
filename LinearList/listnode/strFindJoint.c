#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct node{
    ElemType data;
    struct node* next;
}LNode;

// 初始化链表
LNode* initList() {
    LNode* head = (LNode*)malloc(sizeof(LNode));
    if (head == NULL) {
        printf("开辟节点失败！\n");
        exit(1);
    }
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
    
    return newnode;
}

// 尾插法（不带头节点，用于初始化公共部分）
LNode* insertLastWithoutHead(LNode* head, ElemType e) {

    if (head->data == '\0') {
        head->data = e;
        head->next = NULL;
        return head;
    }
    else {
        LNode* newnode = (LNode*)malloc(sizeof(LNode));
        if (newnode == NULL) {
            printf("开辟节点失败！\n");
            exit(1);
        }
        newnode->data = e;
        newnode->next = NULL;
        LNode* lastnode = getLast(head);
        lastnode->next = newnode;

        return newnode;
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
}



// 初始化字符串链表 传入头节点和 字符串首地址
void initString(LNode* head, ElemType* p) {
    while (*p != '\0' && p != NULL) {
        insertLast(head, *p);
        p++;
    }
    if (p == NULL) {
        printf("Invalid Input!\n");
        freeList(head);
        return;
    }
}


// 初始化字符串链表 （不带头节点）
void initStringWithoutHead(LNode* head, ElemType* p) {
    head->data = '\0';
    while (*p != '\0' && p != NULL) {
        insertLastWithoutHead(head, *p);
        p++;
    }
    if (p == NULL) {
        printf("Invalid Input!\n");
        freeList(head);
        return;
    }
}

// 获取链表长度
int getLength(LNode* head) {
    int count = 0;
    LNode* p = head;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

// 连接单独部分与公共部分
void jointStr(LNode* head, LNode* joint) {
    LNode* tail = getLast(head);
    tail->next = joint;
}

// 找到第一个公共部分 返回公共部分的起始节点
LNode* getJointPos(LNode* str1, LNode* str2, int length1, int length2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    LNode* fast = str1;
    LNode* slow = str2;

    if (length1 < length2) {
        fast = str2;
        slow = str1;
    }
    else {};
    
    // int count = 0;
    for (int i = 0; i < abs(length1 - length2); i++) {
        fast = fast->next;
        // count++;
    }
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
        if (fast == NULL || slow == NULL) {
            printf("Error!\n");
            return NULL;
        }
        // count++;
    }
    // return count;
    return fast;
}

// 打印链表内容
void printNode(LNode* head) {
    // 遍历链表输出节点的data
    LNode* temp = head->next;
    printf("Node data:");
    while (temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    LNode* str1 = initList();
    LNode* str2 = initList();
    LNode* strJoint = initList();

    ElemType inputStr[50];
    printf("Input str1 seperate:\n");
    scanf("%s", inputStr);
    initString(str1, inputStr);
    printf("Input str2 seperate:\n");
    scanf("%s", inputStr);
    initString(str2, inputStr);
    printf("Input str joint:\n");
    scanf("%s", inputStr);
    initStringWithoutHead(strJoint, inputStr);

    jointStr(str1, strJoint);
    jointStr(str2, strJoint);

    int length1 = getLength(str1);
    int length2 = getLength(str2);
    
    printNode(str1);
    printNode(str2);

    printf("%c\n", getJointPos(str1, str2, length1, length2)->data);

    freeList(str1);

    return 0;
}