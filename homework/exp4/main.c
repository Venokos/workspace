#include <stdio.h>
#include <string.h>

#define N 5

// 铁路购票系统
// 车厢共20排，每一排有5个座位，购票时最多购买5张
// 如果能安排在【同一排相邻座位】，则安排在编号最小的相邻座位，否则安排在编号最小的几个空座位中（不考虑是否相邻）。

int main(void)
{
    int times = 0; // 购票次数
    int tickets[N]; // 每次购票张数
    char seats[20][5][3]; // 座位表 20行5列，每个座位名称最多3个字符 (e.g. 20A)
    int occupied[20][5] = {0}; // 是否占座，空=0,占=1

    // 初始化座位表(1A 1B 1C 1D 1F, ..., 20D, 20F)
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 4; j++) {
            sprintf(seats[i][j], "%d%c", i+1, 'A'+j);
        }
        sprintf(seats[i][4], "%d%c", i+1, 'F');
    }

    scanf("%d", &times);
    for (int i = 0; i < times; i++) {
        scanf("%d", &tickets[i]);
    }

    for (int t = 0; t < times; t++) {
        int n = tickets[t];
        if (n > 5 || n <= 0) {
            continue; // 非法输入
        }

        int assigned = 0; // 用于判断相邻座位是否安排成功，成功=1,不成功=0

        // 先尝试安排相邻座位：逐排扫描，寻找连续n个空座位，找到后立即分配
        for (int row = 0; row < 20 && !assigned; row++) {
            int consecutive = 0; // 统计该排座位连续座位数
            int start_col = -1; // 相邻座位 最小编号

            // 对于本排的每个座位
            for (int col = 0; col < 5; col++) {
                if (!occupied[row][col]) { // 如果该座位没有被占
                    if (consecutive == 0) start_col = col;
                    consecutive++;
                    if (consecutive >= n) { // 如果有足够的连续座位
                        // 打印座位号
                        for (int i = 0; i < n; i++) {
                            printf("%s", seats[row][start_col + i]);
                            occupied[row][start_col + i] = 1;
                            if (i < n-1) printf(" "); // 要求每行输出的最后一个座位号后没有空格
                        }
                        printf("\n");
                        assigned = 1; // 安排成功，assigned置1
                        break;
                    }
                }
                else { // 遇到已占座位，重置计数
                    consecutive = 0;
                    start_col = -1;
                }
            }
        }

        // 如果未找到相邻座位，则分散分配
        if (!assigned) {
            int count = 0; // 记录已分配的座位数
            // 遍历所有座位
            for (int row = 0; row < 20 && count < n; row++) {
                for (int col = 0; col < 5 && count < n; col++) {
                    if (!occupied[row][col]) { // 如果该座位为空
                        printf("%s", seats[row][col]);
                        occupied[row][col] = 1;
                        count++;
                        if (count < n) printf(" "); // 要求每行输出的最后一个座位号后没有空格
                    }
                }
            }
            printf("\n");
        }
    }

    return 0;
}
