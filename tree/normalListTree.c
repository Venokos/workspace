#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct TreeNode {
    ElemType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
} TreeNode;

typedef TreeNode* BiTree;

char data[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;

// 利用前序遍历创建树
BiTree createTree() {

    char ch = data[idx++];

    if (ch == '#') {
        return NULL;
    }
    
    BiTree T = (BiTree)malloc(sizeof(TreeNode));
    if (T == NULL) {
        printf("Memory Allocation Failed.\n");
        return NULL;
    }

    T->data = ch; 
    T->lchild = createTree();  
    T->rchild = createTree();

    return T;
}

// 前序遍历
void preOrder(BiTree T) {
    if (T == NULL) {
        return;
    }
    printf("%c ", T->data);
    preOrder(T->lchild);
    preOrder(T->rchild);

}

// 中序遍历
void inOrder(BiTree T) {
    if (T == NULL) {
        return;
    }
    inOrder(T->lchild);
    printf("%c ", T->data);
    inOrder(T->rchild);

}

// 后序遍历
void postOrder(BiTree T) {
    if (T == NULL) {
        return;
    }

    postOrder(T->lchild);
    postOrder(T->rchild);
    printf("%c ", T->data);

}

// 释放树内存
void freeTree(BiTree T) {
    if (T != NULL) {
        freeTree(T->lchild);
        freeTree(T->rchild);
        free(T);
    }
}

int main() {

    BiTree T = createTree();

    printf("preOrder: ");
    preOrder(T);
    printf("\n");
    printf("inOrder: ");
    inOrder(T);
    printf("\n");
    printf("postOrder: ");
    postOrder(T);
    printf("\n");

    free(T);
    
    return 0;
}