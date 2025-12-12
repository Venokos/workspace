#include <stdio.h>

typedef struct student {
        int score[20];
        float aver;
    }STUDENT;

void InputScores(int n, int m, STUDENT* stu);
void FindMaxMin(int i, int m, STUDENT* stu);
void GetAver(int i, int m, STUDENT* stu);
void GetMaxAver(int n, int m, STUDENT* stu);

int main()
{
    int n = 0, m = 0;
    int ret = scanf("%d %d", &n, &m);
    if (ret != 2 || n < 0 || m < 0 || n > 100 || m > 20) return -1;
    STUDENT stu[100];
    InputScores(n, m, stu);
    int i = 0;
    for (; i < n; i++) {
        FindMaxMin(i, m, stu);
        GetAver(i, m, stu);
    }
    GetMaxAver(n, m, stu);

    return 0;
}

// 用户输入得分 n:同学数(<=100) m:评委数(<=20)
void InputScores(int n, int m, STUDENT* stu) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &stu[i].score[j]);
        }
    }
}

// 找到每一名选手的最高和最低分
// i:第i位选手 m：评委数
void FindMaxMin(int i, int m, STUDENT* stu) {
    int k = 0, l = 0;
    for (int a = 0; a < m; a++) {
        if (stu[i].score[k] < stu[i].score[a]) k = a; // 如果当前下标更大，则更新最大值
        if (stu[i].score[l] > stu[i].score[a]) l = a; // 如果当前下标更小，则更新最小值
    }
    // 循环结束后，k是最大值下标，l是最小值下标
    stu[i].score[k] = 0, stu[i].score[l] = 0;
}

// i:第i位选手 m：评委数
void GetAver(int i, int m, STUDENT* stu){
    int sum = 0;
    for (int a = 0; a < m; a++) {
        sum += stu[i].score[a];
    }
    stu[i].aver = (float)sum / (m-2);
}

// 求得最大平均值对应下标，并打印最大平均值
// n:同学数(<=100) m:评委数(<=20)
void GetMaxAver(int n, int m, STUDENT* stu) {
    int j = 0;
    for (int k = 0; k < n; k++) {
        if (stu[k].aver > stu[j].aver) j = k; // 如果当前下标的平均值比记录的平均值更大，则更新平均值
    }
    printf("%.2f", stu[j].aver);
}
