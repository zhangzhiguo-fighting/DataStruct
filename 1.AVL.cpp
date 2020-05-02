/*************************************************************************
	> File Name: 1.AVL.cpp
	> Author: 
	> Mail: 
	> Created Time: 四  4/23 18:16:16 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*简化*/
#define H(root) (root)->h
#define K(root) (root)->key
#define L(root) (root)->lchild
#define R(root) (root)->rchild

typedef struct Node {
    int key, h;
    struct Node *lchild, *rchild;
} Node;

/*解决访问空指针的属性会出错的情况*/
Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = NIL->h = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}


Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->h = 1;
    p->lchild = p->rchild = NIL;
    return p;
}

void update_height(Node *root) {
    root->h = (H(L(root)) > H(R(root)) ? H(L(root)) : H(R(root))) + 1; //最大的子树高度+1
    return ;
}

/*左旋*/
Node *left_rotate(Node *root) {
    Node *temp = root->rchild; //记录新的根结点
    root->rchild = temp->lchild; //转一下，砍一刀；左旋砍掉新根结点的左孩子
    temp->lchild = root; //把root接到新根结点下
    update_height(root);
    update_height(temp);
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    update_height(root);
    update_height(temp);
    return temp;
}

/*调整*/
Node *maintain(Node *root) {
    if (abs(H(L(root)) - H(R(root))) <= 1) return root;
    if (H(L(root)) > H(R(root))) { //一定会进行一次大右旋
        if (H(R(L(root))) > H(L(L(root)))) { //如果满足LR
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (H(L(R(root))) > H(R(R(root)))) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    update_height(root);
    return maintain(root);
}

/*寻找前驱*/
Node *predeccessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) {
        root->lchild = erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild =erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) { //删除度为0，1的点
            Node *temp = root->rchild == NIL ? root->rchild : root->lchild;
            free(root);
            return temp;
        } else {
            Node *temp = predeccessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    return maintain(root);
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d, %d, %d)\n", K(root), K(L(root)), K(R(root)));
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    #define MAX_OP 20
    Node *root = NIL;
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        root = insert(root, val);
    }
    output(root);
    int val;
    while (~scanf("%d", &val)) {
        root = erase(root, val);
        printf("erase %d from AVL tree\n", val);
        output(root);
    }
    return 0;
}


