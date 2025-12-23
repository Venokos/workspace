#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
    ElemType data;
    struct node* next;
}LNode, *Linklist;
// LNode是一个节点对象，Linklist是一个指针

Linklist head = NULL; // head是一个链表头指针

// 头插法 传入头节点和要插入的数据
void insertHead(LNode* L, ElemType e) {
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    newNode->data = e;
    newNode->next = L->next;
    L->next = newNode;

    head->data++; // head的data存储节点个数
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
LNode* insertLast(int e) {
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

    head->data++;
    return 1;
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

// 查找链表中倒数第k个位置上的节点
int find_node(unsigned int k){
    if (k > head->data) return 0; // 超出链表长度，返回0
    LNode* current = head->next;
    for (int i = 0; i < head->data - k;i++) {
        current = current->next;
    }
    printf("Node Found:%d\n", current->data);
    return 1;
}

// 查找链表中倒数第k个位置上的节点（快慢指针）
int find_node_pro(LNode* head, int k){
    LNode* Fast = head->next;
    LNode* Slow = head->next;
    for (int i = 0; i < k; i++) {
        Fast = Fast->next;
    }
    while (Fast != NULL) {
        Fast = Fast->next;
        Slow = Slow->next;
    }
    if (Slow == NULL) return 0;
    else {
        printf("Node found:%d\n", Slow->data);
        return 1;
    }
}


// 释放内存
void freeList() {
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
    head = (Linklist)malloc(sizeof(LNode));
    if (head == NULL) {
        printf("开辟节点失败！\n");
        exit(1);
    }
    head->data = 0; // 记录链表节点数
    head->next = NULL;

    LNode* last = getLast(head);

    last = insertLast(3);
    last = insertLast(7);
    last = insertLast(5);
    last = insertLast(9);
    last = insertLast(7);
    last = insertLast(5);
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

    insertHead(head, 8);
    insertHead(head, 10);
    printNode();

    insertPos(head, 2, 20);
    printNode();

    find_node_pro(head, 4);
    
    freeList();
    printf("%d\n",head->data);
    return 0;
}