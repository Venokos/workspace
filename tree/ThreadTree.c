#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct TreeNode {
    ElemType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int ltag;
    int rtag;
} TreeNode;

typedef TreeNode* ThreadTree;

char data[] = "ABDH##I##EJ###CF##G##";
int idx = 0;
ThreadTree prev = NULL; // 全局变量，用于记录前驱结点

// 利用前序遍历创建树
ThreadTree createTree() {

    char ch = data[idx++];

    if (ch == '#') {
        return NULL;
    }
    
    ThreadTree T = (ThreadTree)malloc(sizeof(TreeNode));
    if (T == NULL) {
        printf("Memory Allocation Failed.\n");
        return NULL;
    }

    T->data = ch; 
    T->lchild = createTree();   
    T->rchild = createTree(); 
    T->ltag = T->lchild ? 0 : 1; // 如果有左孩子则tag为0,左孩子为空则tag为1
    T->rtag = T->rchild ? 0 : 1;

    return T;
}

// 中序线索化函数，建立前驱/后继关系
// 将 最后一个输出结点 以外 的所有结点线索化了，包含将 第一个输出结点lchild指向head 的 步骤
// 也是 中序遍历 的思想 左->根->右
void threading(ThreadTree T) {
    if (T != NULL) {
        threading(T->lchild); // 递归线索化左子树

        // 如果当前结点的左孩子为空(ltag == 1)，建立前驱线索
        if (T->ltag) {
            T->lchild = prev;
        }
        // 如果 前一个结点 不为空 且 右孩子为空(rtag == 1)，建立后继线索
        // 实际上本例中prev不可能为空。这里为增强代码健壮性可以多判断一下
        if (prev && prev->rtag) {
            prev->rchild = T;
        }

        prev = T; // 更新prev为当前结点

        threading(T->rchild); // 递归线索化右子树

    }
}

// 创建头节点，建立中序线索二叉树
void inOrderThreading(ThreadTree* T, ThreadTree* head) {
    *head = (ThreadTree)malloc(sizeof(TreeNode));
    if (*head == NULL) {
        printf("Memory Allocation Failed.\n");
        return;
    }
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->rchild = (*head); // 初始时回指自己

    // 如果传入空树
    if (*T == NULL) {
        (*head)->lchild = (*head);
    }
    else {
        (*head)->lchild = *T; // 1.头结点的左孩子指向根结点
        prev = *head; // 初始化前驱指针
        threading(*T); // 中序线索化整棵树

        // 调整最后一个结点的后续线索
        (*head)->rchild = prev; // 2.头结点的右孩子 指向 遍历的最后一个结点
        prev->rchild = *head; // 3.遍历的最后一个结点 的 右孩子 指向 头结点
    }
}


// 中序遍历线索二叉树（非递归）（也是中序的思想 左->根->右）
void inOrderPlus(ThreadTree head) {
    ThreadTree curr = head->lchild; // 从左子树开始
    while (curr != head) {
        // 如果有左孩子，沿着左孩子一直走到最底
        while (curr->ltag == 0) {
            curr = curr->lchild;
        }
        // 访问当前结点
        printf("%c ", curr->data);
        // 沿着线索一直向右访问所有后继
        while (curr->rtag == 1 && curr->rchild != head) {
            curr = curr->rchild;
            printf("%c ", curr->data);
        }

        // 进入当前结点的右子树
        curr = curr->rchild;
    }

}

// 释放树内存
void freeTree(ThreadTree T) {
    if (T != NULL) {
        freeTree(T->lchild);
        freeTree(T->rchild);
        free(T);
    }
}

int main() {

    ThreadTree T = createTree();
    ThreadTree head = NULL;
    inOrderThreading(&T, &head);

    printf("inOrderPlus: ");
    inOrderPlus(head);
    printf("\n");

    free(T);
    
    return 0;
}