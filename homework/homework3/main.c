#include <stdio.h>
#include <string.h>

int main()
{
//    // Q5
//    char input_day[15];
//    char days[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday",
//                        "Thursday", "Friday", "Saturday"};
//    printf("Input a day: ");
//    scanf("%s", input_day);
//    int found = 0;
//    for (int i = 0; i < 7; i++) {
//        if (strcmp(days[i], input_day) == 0) {
//            found = 1;
//            printf("%d", i);
//        }
//    }
//    if (!found) printf("Not Found!\n");

    // Q6
//    typedef struct date {
//        int year;
//        int month;
//        int day;
//    }DATE;
//
//    typedef struct occpuation {
//        char college[100];
//        char title[50];
//        char content[200];
//    }JOB;
//
//    typedef struct student {
//        char name[50];
//        char sex;
//        DATE birthday;
//        JOB situation;
//    }STU;
//
//    STU stu_input[5];
//    DATE cmpage[5];
//    for (int i = 0; i < 5; i++) {
//        scanf("%s", stu_input[i].name);
//        scanf(" %c", &stu_input[i].sex); // a space to absorb '\n'
//        scanf("%d %d %d", &stu_input[i].birthday.year,
//        &stu_input[i].birthday.month, &stu_input[i].birthday.day);
//        scanf("%s %s %s", stu_input[i].situation.college,
//        stu_input[i].situation.title, stu_input[i].situation.content);
//
//        cmpage[i] = stu_input[i].birthday;
//    }
//    int oldest = 0; // assume that person 0 is the oldest
//    for (int i = 0; i < 5; i++) {
//        if (cmpage[i].year < cmpage[oldest].year) oldest = i;
//        else if (cmpage[i].year == cmpage[oldest].year) {
//            if (cmpage[i].month < cmpage[oldest].month) oldest = i;
//            else if (cmpage[i].month == cmpage[oldest].month) {
//                if (cmpage[i].day < cmpage[oldest].day) oldest = i; // disregard of a completely same birthday
//            }
//        }
//    }
//    printf("The oldest person is: %s", stu_input[oldest].name);

    // Q7 : 给定数组arr, 编写冒泡排序的 C 代码，将数组按从小到大排序，并输出排序后的数组
    int arr[6] = {9, 3, 7, 1, 6, 2};
    int n = 6;
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        int swap = 0; // 标记本轮暂未交换
        for (j = 0; j < n-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                // 交换两元素
                temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
                swap = 1; // 发生交换
            }
        }
        if (!swap) break;
    }
    for (i = 0; i < n; i++) printf("%d ", arr[i]);




    return 0;
}
