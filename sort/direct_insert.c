#include <stdio.h>

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 直接插入排序，传入数组和元素个数
void direct_insert_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) { // 从第二个元素开始遍历整个数组
        if (arr[i] < arr[i-1]) { // 如果当前元素比上一个元素小，则需要插入
            int temp = arr[i];
            int j = i-1;
            for (; j >= 0 && arr[j] > temp; j--) { // 找到合适的插入位置
                arr[j+1] = arr[j]; // 同时将元素后移
            }
            arr[j+1] = temp; // 找到合适位置后插入该元素
        }
        printf("第%d趟：", i);
        print_array(arr, n);
    }
}



int main() {
    int test_array[10] = {45, 27, 20, 60, 55, 7, 71, 36, 44, 67};
    direct_insert_sort(test_array, 10);
    print_array(test_array, 10);



    return 0;
}