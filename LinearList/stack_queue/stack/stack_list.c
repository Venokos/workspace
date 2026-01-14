#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElemType;

// 链表储存栈元素
typedef struct stack {
    ElemType data;
    struct stack* next;
    int top;
} Stack;

// 初始化栈
Stack* initStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->next = NULL;
    stack->top = -1;
    return stack;
}

// 判空
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 压栈（头插法）
int push(Stack* stack, ElemType value) {
    if (stack->top == MAXSIZE - 1) {
        printf("The stack is full!\n");
        return -1;
    }
    stack->top++;
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    newNode->data = value;
    newNode->next = stack->next;
    stack->next = newNode;
    return 0;
}

// 出栈
int pop(Stack* stack, ElemType *e) {
    if (isEmpty(stack)) {
        printf("The stack is empty!\n");
        return -1;
    }
    *e = stack->next->data;
    Stack* temp = stack->next;
    stack->next = temp->next;
    free(temp);
    stack->top--;
    return 0;
}

// 获取栈顶元素
int peek(Stack* stack, ElemType *e) {
    if (isEmpty(stack)) {
        printf("The stack is empty!\n");
        return -1;
    }
    *e = stack->next->data;
    return 0;
}

// 清空栈
void freeStack(Stack* stack) {
    Stack* current = stack->next;
    while (current != NULL) {
        Stack* temp = current;
        current = current->next;
        free(temp);
    }
    free(stack);
}


int main() {
    Stack* stack = initStack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    ElemType e;
    pop(stack, &e);
    printf("Popped: %d\n", e);
    peek(stack, &e);
    printf("Peeked: %d\n", e);

    freeStack(stack);
    return 0;
}

