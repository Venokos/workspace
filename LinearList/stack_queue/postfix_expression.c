#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 程序：计算后缀表达式的值

// 定义栈中元素的最大个数
#define MAX_SIZE 100

typedef int ElemType;

typedef struct {
  ElemType *data;
  int top;
} Stack;

typedef enum {
    LEFT_PARE, RIGHT_PARE,
    ADD, SUB, MUL, DIV, MOD,
    EOS, NUM
} contentType;

// 初始化栈
Stack* Stack_Init() {
    Stack* S = (Stack*)malloc(sizeof(Stack));
    if (S == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    S->data = (ElemType *)malloc(MAX_SIZE * sizeof(ElemType)); // 动态分配内存储存栈元素
    if (S->data == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    S->top = -1; // 初始化栈顶指针为-1，表示栈为空

    return S;
}

// 判断栈是否为空
int isEmpty(Stack *S) {
  return S->top == -1;
}

// 判断栈是否已满
int isFull(Stack *S) {
  return S->top == MAX_SIZE - 1;
}


// 新元素入栈
int Push(Stack *S, ElemType x) {
    if (isFull(S)) {
        printf("栈已满，无法入栈\n");
        return 0;
    } 
    else {
        S->data[++S->top] = x; // 将元素入栈，并更新栈顶指针
        return 1;
    }
}

// 出栈 x为栈顶元素
int Pop(Stack *S, ElemType *x) {
    if (isEmpty(S)) {
        printf("栈为空，无法出栈\n");
        return 0;
    }
    else {
        *x = S->data[S->top--];
        return 1;
    }
}

// 读取元素类型
contentType getToken(Stack *S, int index, char* expr) {
    char content = expr[index];
    switch (content)
    {
    case '+':
        return ADD;
    case '-':
        return SUB;
    case '*':
        return MUL;
    case '/':
        return DIV;
    case '%':
        return MOD;
    case '(':
        return LEFT_PARE;
    case ')':
        return RIGHT_PARE;
    case '\0':
        return EOS;
    default:
        return NUM;
    }
}

// 计算表达式
int getResult(Stack* S, char* expr) {
    int index = 0;
    int num1, num2;
    
    contentType token = getToken(S, index, expr);
    // while (1) {
    //     contentType token = getToken(S, index, expr);
    //     if (token == EOS) {
    //         break;
    //     }
    while (token != EOS) {
        char content = expr[index];
        index++;

        if (token == NUM) {
            // 字符转换为数字的常用技巧，原理是ASCII码之间相差的数值
            // 例如: '8' - '0'
            Push(S, content - '0'); 
        }
        else {
            Pop(S, &num1);
            Pop(S, &num2);

            switch (token) {
                case ADD:
                    Push(S, num2 + num1);
                    break;
                case SUB:
                    Push(S, num2 - num1);
                    break;
                case MUL:
                    Push(S, num2 * num1);
                    break;
                case DIV:
                    if (num1 == 0) {
                        printf("0 can't be devided.\n");
                        return -1;
                    }
                    Push(S, num2 / num1);
                    break;
                case MOD:
                    if (num1 == 0) {
                        printf("0 can't be devided.\n");
                        return -1;
                    }
                    Push(S, num2 % num1);
                    break;
                // 注：前/后缀表达式没有括号
                case LEFT_PARE:
                    break;
                case RIGHT_PARE:
                    break;
                default:
                    printf("Unknown Error.\n");
                    return -1;
            }
        }
        token = getToken(S, index, expr);
    }
    // 如果最后栈中只剩一个元素，说明计算完成
    if (S->top == 0) {
        int result;
        Pop(S, &result);
        return result;
    }
    else {
        printf("Wrong expression!\n");
        return -1;
    }
}


int main() {
    char expr[] = "82/2+56*-";

    Stack* S = Stack_Init();
    int result = getResult(S, expr);
    printf("result:%d\n", result);




    return 0;
}