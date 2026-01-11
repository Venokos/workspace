#include <stdio.h>
#include <string.h>

int check(char *str, char *substr)
{
    int x, y, z, num = 0;
    for (x = 0; str[x] != '\0'; x++)
    {
        for (y = x, z = 0; str[y] == substr[z]; y++, z++)
        {
            if (substr[z + 1] == '\0')
            {
                num++;
                break;
            }
        }
    }
    return num;
}


int main() {
    FILE *fp = fopen("test.txt", "w");
    if (fp == NULL) {
        return -1;
    }
    char* str = "WOrldddddd";
    char* str2 = "Hello";
    
    for (int i = 0; i < strlen(str2); i++) {
        putc(str2[i], fp);
    }


    char *p[10] = { "abc", "aabdfg", "dcabe", "abbd", "cd" };
    printf("%zu\n", strlen(p[4]));
    printf("%c\n", *p[4]);
    printf("%s\n", p[4]);

    printf("%d\n", check("abchelloabhghellocde", "hello"));

    int arr[] = {1, 7, 8, 9};
    fprintf(stdout, "%zu\n", sizeof(arr));
    
    // while(getchar() != '\n');

    struct Student {
    char name[100];
    // ...
    } student[50];
    for (int q = 0; q < 49; q++) {
        strcpy(student[q].name, "Lebron James\n");
    }
    strcpy(student[1].name, "wwsg\n");
    strcpy(student[49].name, "Stephen Curry\n");
    FILE* fp2 = fopen("test.txt", "a");
    for (int i = 0; i < 50; i++) {
        fwrite(student, 25 * sizeof(struct Student), 25, fp);
    }
    fclose(fp);
    fclose(fp2);
    return 0;
}