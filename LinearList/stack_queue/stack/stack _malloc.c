#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义栈中元素的最大个数
#define MAX_SIZE 100

typedef struct stack{
  char *data;
  int top;
} SqStack;


// 初始化栈
void Stack_Init(SqStack *S) {
  S->top = -1; // 初始化栈顶指针为-1，表示栈为空
  S->data = (char *)malloc(MAX_SIZE * sizeof(char)); // 动态分配内存储存栈元素
}

// 判断栈是否为空
int Stack_Empty(SqStack S) {
  return S.top == -1;
}


// 判断栈是否已满
int Stack_Full(SqStack S) {
  return S.top == MAX_SIZE - 1;
}


// 新元素入栈
int Stack_Push(SqStack *S, char x) {
  if (Stack_Full(*S)) {
    printf("栈已满，无法入栈\n");
    return 0;
  } 
  else {
    S->data[++S->top] = x; // 将元素入栈，并更新栈顶指针
    return 1;
  }
}

// 出栈 x为栈顶元素
int Stack_Pop(SqStack *S, char *x) {
  if (Stack_Empty(*S)) {
    printf("栈为空，无法出栈\n");
    return 0;
  }
  else {
    *x = S->data[S->top--];
    return 1;
  }
}


int main() {
  SqStack stack;
  Stack_Init(&stack);
  char string[MAX_SIZE];
  printf("Enter a string:"); // 假设输入不带空格
  scanf("%s", string);

  // 入栈
  for (int i = 0; i < strlen(string); i++) {
    Stack_Push(&stack, string[i]);
  }
  // 出栈
  for (int i = 0; i < strlen(string); i++) {
    printf("%c", stack.data[stack.top]);
    Stack_Pop(&stack, &stack.data[stack.top]);
  }  
  // char x;
  // while (Stack_Pop(&stack, &x)) {
  //   printf("%c", x);
  // }
  printf("\n");


  return 0;
}