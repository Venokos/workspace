#include <stdio.h>


int main()
{
    int EveryMonth[20] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = 1990, month = 1, day = 1;
    // 用户输入
    printf("Input YYYY-MM-DD:");
    int ret = scanf("%4d-%2d-%2d", &year, &month, &day);
    // 用户输入检查
    int flag = 0; // 如果输入错误，flag置1,执行ERR的语句
    int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (year < 1990 || month < 1 || month > 12 || ret != 3 || day < 1 || day > 31) {
        flag = 1;
        goto ERR;
        }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            flag = 1;
            goto ERR;
        }
    }
    else if (month == 2) {
    // 如果是平年，且二月份天数大于28，则返回输入错误
            if (!leap) {
                if (day > 28) {
                    flag = 1;
                    goto ERR;
                    }
                }
            else {
                if (day > 29) {
                    flag = 1;
                    goto ERR;
                    }
                }
            }
    else { // 大月31天
        if (day > 31) {
            flag = 1;
            goto ERR;
            }
        }
    // 计算过了多少年
    int delta_years = year - 1990;
    // 统计闰年次数
    int count = 0;
    for (int i = 1990; i < year; i++) {
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) count++;
    }
    // 计算月份之间相差的天数
    int total_month_days = 0;
    for (int j = 0; j < month-1; j++) {
        total_month_days += EveryMonth[j];
    }
    // 计算相差几日
    int delta_days = day;
    int total_days = delta_years * 365 + count + total_month_days + delta_days;
    // 判断是否在工作
    if (total_days % 5 == 4 || total_days % 5 == 0) printf("rest\n");
    else printf("working\n");

    // 统一处理错误输入
    ERR:
        if (flag) printf("Invalid input\n");

    return 0;
}
