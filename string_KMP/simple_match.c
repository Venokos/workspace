#include <stdio.h>
#include <string.h>

int count = 0;

int simple_match(const char* s1, const char* s2) {
    int n = strlen(s1);
    int m = strlen(s2);
    if (n < m) return -1;
    for (int i = 0; i <= n - m; i++) {
        int j = 0, k = i;
        for (; j < m; j++) {
            count++;
            if (s1[k] == s2[j]) {
                if (j == m - 1) {
                    return i;
                }
                k++;
            }
            else {
                break;
            }
        }
    }
    return -1;


}


int main() {

    char s1[] = "abaabaabacacaabaabcc";
    char s2[] = "abaabc";
    printf("%p\n", strstr(s1, s2));
    printf("%p\n", &s1[3]);


    printf("pos:%d, count:%d\n", simple_match(s1, s2), count);
    printf("count:%d\n", count);

    // 发现一个有趣的现象！这里的count如果和pos一起输出会输出0,而分开输出则输出正常数字。

    // 问题根源：参数求值顺序未指定 （编译器可能先计算了count，再计算函数）

    // 在C语言中，函数参数的求值顺序是未指定的（unspecified）。这意味着：

    // 编译器可以以任意顺序计算函数参数的值

    // 不同的编译器、不同的优化级别可能会有不同的顺序

    // 这属于C标准的合法行为

    
    return 0;
}