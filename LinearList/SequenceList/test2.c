#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef int ElemType; // 方便后续修改元素数据类型 （高内聚 低耦合）

// 利用动态内存分配，在堆上 为 结构体和其中的数组创建空间

typedef struct {
    ElemType *data;
    int length;
}SeqList;

// 初始化：在函数体内创建结构体，并返回指向该结构体的指针
SeqList* initList() {
    SeqList* L  = (SeqList*)malloc(sizeof(SeqList)); // 在堆上开辟结构体
    L->data = (ElemType*)malloc(sizeof(ElemType) * MAX_SIZE); // 在堆上开辟数组
    L->length = 0;
    return L;  
}

// 尾部插入元素
int appendElem(SeqList* L, ElemType e) {
    if (L->length >= MAX_SIZE) {
        printf("The list is full!\n");
        return 0;
    }
    L->data[L->length] = e;
    L->length++;
    return 1;
}
// 遍历输出顺序表内容
void printList(SeqList* L) {
    for (int i = 0; i < L->length; i++) {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}
// 插入元素 pos代表插入位置，不是下标
int insertElem(SeqList *L, int pos, ElemType e) {
    if (L->length >= MAX_SIZE) {
        printf("The list is full!\n");
        return 0;
    }
    if (pos < 1 || pos > L->length) {
        printf("Wrong position!\n");
        return 0;
    }
    for (int i = L->length - 1; i >= pos - 1; i--) {
        L->data[i+1] = L->data[i];
    }
    L->data[pos-1] = e;
    L->length++;
    return 1;
}
// 删除元素 e用于存储删除的数据
int deleteElem(SeqList *L, int pos, ElemType *e) {
    if (L->length == 0) {
        printf("Empty list!\n");
        return 0;
    }
    if (pos < 1 || pos > L->length) {
        printf("Wrong position!\n");
        return 0;
    }
    *e = L->data[pos-1];
    for (int i = pos - 1; i < L->length; i++) {
        L->data[i] = L->data[i+1];
    }
    L->length--;
    return 1;
}
// 查找 如果查找成功，返回元素位置（不是下标）
int findElem(SeqList *L, ElemType e) {
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == e) return i + 1;
    }
    return 0;
}


int main() {
    SeqList* list = initList();
    printf("初始化顺序表成功，当前顺序表长度:%d\n", list->length);
    printf("顺序表内存占用:%zu\n", sizeof(list->data));
    appendElem(list, 40);
    appendElem(list, 42);
    appendElem(list, 46);
    appendElem(list, 57);
    printList(list);

    insertElem(list, 2, 88);
    printList(list);

    ElemType deleted;
    deleteElem(list, 2, &deleted);
    printList(list);
    printf("被删除数据:%d\n", deleted);

    int find = 46;
    printf("找到元素:%d,位于位置:%d\n", find, findElem(list, find));

    return 0;
}