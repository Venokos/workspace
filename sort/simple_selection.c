#include <stdio.h>
int main() {
    int arr[10] = {29, 10, 14, 37, 13, 5, 40, 8, 33, 2};
    int n = 10;
 
    // 实现简单选择排序
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[k]) k = j;
        }
        int temp = arr[i];
        arr[i] = arr[k];
        arr[k] = temp;

        printf("第%d趟：", i+1);
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