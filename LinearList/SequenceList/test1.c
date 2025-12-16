#include <stdio.h>

#define MAX_SIZE 100

typedef int ElemType; // 方便后续修改元素数据类型 （高内聚 低耦合）

typedef struct {
    ElemType data;
    int length;
}SeqList;
// 初始化
void initList(SeqList* list) {
    list->length = 0;
}
// 尾部插入元素
int appendElem(SeqList* L, ElemType e) {
    if (L->length >= MAX_SIZE) {
        printf("The list is full!\n");
        return 0;
    }

}

int main() {




    return 0;
}