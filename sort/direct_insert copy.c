#include <stdio.h>
int main() {
    int arr[10] = {23, 5, 12, 7, 31, 19, 1, 8, 15, 4};
    int n = 10;
 
    // 实现直接插入排序
for (int i = 1; i < n; i++) {
     //在此填入代码
   
    if (arr[i] < arr[i-1]) {
        int j = i-1;
        int temp = arr[i];
        for (; j >= 0 && temp < arr[j]; j--)  arr[j+1] = arr[j];
            arr[j+1] = temp;
         }
        printf("第%d趟：", i);
        for (int k = 0; k < n; k++) {
        printf("%d ", arr[k]);
        }
        printf("\n");
    }
 
        printf("排序结果：");
         for (int i = 0; i < n; i++) {
               printf("%d ", arr[i]);
         }
    return 0;
}
