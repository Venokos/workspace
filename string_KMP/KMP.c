#include <stdio.h>
#include <string.h>

// 程序：KMP算法进行字符串匹配


int count = 0; // 全局变量count 统计KMP比较次数

// 获取next数组 传入模式串
void getNext(const char* pattern, int* next) {
    int m = strlen(pattern);
    int i = 0, j = -1;
    next[0] = -1;
    while (i < m) {
        if (j == -1 || pattern[i] == pattern[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

// KMP算法实现 传入主串&模式串
int kmp(const char* str, const char* pattern) {
    // i是主串指针，永不回溯；j是模式串指针，根据next数组回溯
    int i = 0, j = 0; 
    // 获取next数组
    int next[100];
    getNext(pattern, next);

    int n = strlen(str); // 主串长度
    int m = strlen(pattern); // 模式串长度

    // 循环退出条件：i >= n（主串结束了还没匹配成功）或 j >= m（模式串匹配成功）
    while (i < n && j < m) {
        if (j == -1 || str[i] == pattern[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
        count++;
    }
    // 如果模式串指针j==m，说明全部匹配成功
    // 但由于此时i和j都从起始位置自增了m次，故需要返回i-j，才是所要找的起始位置
    if (j == m) {
        return i - j;
    }
    // 若退出循环后不满足j == m，则说明i >= n，主串全部搜索完也没有匹配成功 
    else {
        return -1;
    }
}

int main() {
    char* str = "abaabaabacacaabaabcc";
    char* pattern = "abaabc";
    printf("pos:%d, count:%d\n", kmp(str, pattern), count);
    printf("count:%d\n", count);
    return 0;
}