#include <stdio.h>


int num1[50] = {0}, num2[50] = {0}, num3[51] = {0}; // 可能进位


int main()
{
    int i = 0, count1 = 0, count2 = 0;
    // 输入第一个数
    while (1) {
        char ch;
        scanf("%c", &ch);
        if (ch == '\n') break;
        else {
            num1[count1] = ch - '0'; // 字符与数字转换
            count1++;
        }
    }
    // 输入第二个数
    while (1) {
        char ch;
        scanf("%c", &ch);
        if (ch == '\n') break;
        else {
            num2[count2] = ch - '0'; // 字符与数字转换
            count2++;
        }
    }

    while (i < count1 && i < 50) {
        num1[49-i] = num1[count1-1-i];
        num1[count1-1-i] = 0;
        i++;
    }
    i = 0;
    while (i < count2 && i < 50) {
        num2[49-i] = num2[count2-1-i];
        num2[count2-1-i] = 0;
        i++;
    }

    // 执行大数加法
    int carry = 0;
    for (int i = 49; i >= 0; i--) {
        int sum = num1[i] + num2[i] + carry;  // 加上进位
        num3[i + 1] = sum % 10;               // 结果存储在num3[1..50]
        carry = sum / 10;                     // 计算新的进位
    }
    num3[0] = carry;  // 可能的最高位进位


    int j = 0;
    while (j <= 50 && num3[j] == 0) {
        j++;
    }
    for (;j < 51; j++) printf("%d", num3[j]);

    return 0;
}
