#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 程序：中缀表达式转后缀表达式

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

// 输出对应的运算符
void printToken(ElemType token) {
    switch (token) {
        case ADD :
            printf("+");
            break;
        case SUB :
            printf("-");
            break;
        case MUL :
            printf("*");
            break;
        case DIV :
            printf("/");
            break;
        case MOD :
            printf("*");
            break;
        default:
            printf("Unknown Error.\n");
    }
}

// 计算表达式
int turnToPost(Stack* S, char* expr) {
    int index = 0;
    
    contentType token = getToken(S, index, expr);
    
    // 初始化栈的第一个元素为EOS
    S->top = 0;
    S->data[S->top] = EOS;

    // 运算符在栈内外的优先级
    int inside_stack[] = {0, 19, 12, 12, 13, 13, 13, 0};
    int outside_stack[] = {20, 19, 12, 12, 13, 13, 13, 0};

    while (token != EOS) {
        char content = expr[index];
        index++;

        // 如果当前指向的字符为数字
        if (token == NUM) {
            printf("%c", content);
        }
        // 如果当前指向的是右括号
        else if (token == RIGHT_PARE) {
            ElemType temp;
            // 持续出栈，直到遇到左括号
            while (S->data[S->top] != LEFT_PARE) {           
                Pop(S, &temp);
                printToken(temp);
                if (S->top == -1) {
                    printf("Wrong expression: lacking LEFT_PARE\n");
                    return -1;
                }
            }
            // 把左括号也出栈（不输出）
            Pop(S, &temp);
        }
        // 如果是其他运算符号
        else {
            // 如果当前运算符优先级比栈顶元素优先级高，则直接压栈
            if (outside_stack[token] > inside_stack[S->data[S->top]]) {
                Push(S, token);
            }
            // 反之（优先级 小于等于 栈顶元素），则“置换”
            else {
                // 栈顶元素出栈
                ElemType temp;
                Pop(S, &temp);
                // 输出栈顶元素对应的运算符
                printToken(temp);
                // 当前运算符压栈
                Push(S, token);
            }
        }
        token = getToken(S, index, expr);

        // 错误处理
        if (S->top == -1) {
            printf("Wrong Expression!\n");
            return -1;
        }
    }
    // 表达式读完后，把栈中剩余元素全部出栈并输出
    while (S->data[S->top] != EOS) {
        // 栈顶元素出栈
        ElemType temp;
        Pop(S, &temp);
        // 输出栈顶元素对应的运算符
        printToken(temp);

        if (S->top == -1) {
            printf("Wrong Expression!\n");
            return -1;
        }
    }

    // 如果最后栈中只剩一个元素，说明转换成功
    if (!(S->top == 0)) {
        printf("Wrong expression!\n");
        return -1;
    }

    printf("\n");

    return 0;
}


int main() {
    char expr1[] = "8/2+2-5*6";
    char expr2[] = "x/(i-j)*y";
    char expr3[] = "a*(b+c)-d";

    Stack* S = Stack_Init();
    turnToPost(S, expr1);
    turnToPost(S, expr2);
    turnToPost(S, expr3);


    return 0;
}