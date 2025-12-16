#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}LNode, *Linklist;
// LNode是一个节点对象，Linklist是一个指针

Linklist head = NULL; // head是一个链表头指针

// 尾插法
void insertLast(int e) {
    LNode* newnode; // newnode是一个指向新节点的指针
    newnode = (LNode *)malloc(sizeof(LNode));
    newnode->data = e;
    newnode->next = NULL;

    LNode* lastnode = head;
    while (lastnode->next != NULL) {
        lastnode = lastnode->next; // 找到插入前最后一个节点
    }
    lastnode->next = newnode; // 插入前最后一个节点指向新节点
    
    head->data ++; // 节点个数+1
}
// 打印链表内容
void printNode() {
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
// 非递归删除所有值为x的节点
void DeleteNode(int x) {
    LNode* current = head;
    while (current != NULL) {
        if (current->next->data == x) { // 如果下一个节点需要删除
            LNode* temp = current->next; // 临时存起来下一个节点
            current->next = current->next->next; // 当前节点跳过待删除节点
            free(temp); // 清理待删除节点
            head->data--; // 节点数-1
        }
        current = current->next;
    }
}

// 递归辅助函数：处理从当前节点开始的链表
Linklist deletehelper(Linklist node, int x) {
    // 递归基：到达链表末尾
    if (node == NULL) return NULL;
    // 递归处理后续节点
    node->next = deletehelper(node->next, x);
    // 处理当前节点
    if (node->data == x) {
        Linklist nextNode = node->next;
        free(node);
        head->data--;
        return nextNode;
    }

    return node;
}
// 主函数：递归删除带头节点链表中所有值为x的节点
void Recursive_DeleteNode(Linklist head, int x) {
    if (head == NULL) return; // 检查头节点是否有效
    // 处理头节点后的所有节点
    head->next = deletehelper(head->next, x);
}

// 查找链表中倒数第k个位置上的结点
int find_node(unsigned int k){
    if (k > head->data) return 0; // 超出链表长度，返回0
    LNode* current = head->next;
    for (int i = 0; i < head->data - k;i++) {
        current = current->next;
    }
    printf("Node Found:%d\n", current->data);
    return 1;
}

// 释放内存
void freeList() {
    LNode* current = head; // 当前节点
    LNode* temp; // 临时指针保存下一个节点
    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }
    head = NULL; // 重要：在释放完成后将头指针设置为NULL
}

int main() {
    head = (Linklist)malloc(sizeof(LNode));
    if (head == NULL) {
        printf("开辟节点失败！\n");
        exit(1);
    }
    head->data = 0; // 记录链表节点数
    head->next = NULL;

    insertLast(3);
    insertLast(7);
    insertLast(5);
    insertLast(9);
    insertLast(7);
    insertLast(5);
    printNode();

    DeleteNode(5); // 非递归删除值为5的节点
    printNode();

    Recursive_DeleteNode(head, 7); // 递归删除值为7的节点
    printNode();

    insertLast(3);
    insertLast(7);
    insertLast(5);
    insertLast(9);
    printNode();
    find_node(2); // 查找倒数第二个节点

    freeList();
    return 0;
}