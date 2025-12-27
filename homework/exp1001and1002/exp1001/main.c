#include <stdio.h>


int main()
{
    char a = 0, sign1 = 0, sign2 = 0;
    int result = 0;
    int num1 = 0;
    // ASCII '0' = 48, '9' = 57
    printf("Input an equation(no space):");

        // 读取第一个数
        while(1) {
            a = getchar();
            if (a < 48 || a > 57) {
                sign1 = a; // 记录当前符号
                break; // 结束读取
            }
            num1 = num1 * 10 + (a - 48);
        }
        result = num1; // 存储第一个数
        while(1) {
            num1 = 0;
            while (1) {
                a = getchar();
                if (a < 48 || a > 57) {
                    sign2 = a; // 记录下一个符号
                    break; // 结束读取
                    }
                num1 = num1 * 10 + (a - 48); // 读取下一个数
                }
            if (sign1 == '+') result += num1;
            else if (sign1 == '-') result -= num1;
            else if (sign1 == '*') result *= num1;
            else if (sign1 == '/') result /= num1;
            else if (sign1 == '=') {
                    printf("%d", result);
                    break;
                }
            else {
                printf("错误的运算符:%c", sign1);
                break;
            }
            sign1 = sign2;
        }

    return 0;
}
