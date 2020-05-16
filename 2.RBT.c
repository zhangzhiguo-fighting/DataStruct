/*************************************************************************
	> File Name: 2.RBT.cpp
	> Author:
	> Mail:
	> Created Time: 六  5/16 14:27:40 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1
#define DBLACK 2

typedef struct Node {
    int key;
    int color; // 0 red, 1 black, 2 double black
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor)) //使代码在主函数之前执行 
void init_NIL() {
    NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
    NIL->color = BLACK;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->color = RED;
    return p;
}

bool has_red_child(Node *root) {
    return root->lchild->color == 0 || root->rchild->color == 0;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

Node *insert_maintain(Node *root) {
    if (!has_red_child(root)) return root;
    /*为了方便，这未失衡时，我们也进行了调整*/
    if (root->lchild->color == RED && root->rchild->color == RED) {
        root->color = RED;
        root->lchild->color = root->rchild->color = BLACK;
        return root;
    }

    if (root->lchild->color == RED) {
        if (!has_red_child(root->lchild)) return root;
        if (root->lchild->rchild->color == RED) { //左孩子的右孩子为红色LR，因为是两个红色节点旋转，每条路径上的黑色节点数，没发生变化，所以不用去改颜色
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root); //无论LR还是LL最终都会进行大右旋
    } else {
        if (!has_red_child(root->rchild)) return root;
        if (root->rchild->lchild->color == RED) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

Node *predeccessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase_maintain(Node *root) {//站在父节点看
    if (root->lchild->color != DBLACK &&
        root->rchild->color != DBLACK) return root;
    if (has_red_child(root)) { //情况四，兄弟为红色
        root->color = RED; //往前写了，旋转和改色，可以不分先后，旋转前的根节点改为红色
        if (root->lchild->color == RED) {
            root = right_rotate(root);
            root->rchild = erase_maintain(root->rchild);
        } else {
            root = left_rotate(root);
            root->lchild = erase_maintain(root->lchild);
        }
        root->color = BLACK; //旋转后的根节点改为黑色
        return root;
    }
    //情况一
    if ((root->lchild->color == DBLACK && !has_red_child(root->rchild)) ||
        (root->rchild->color == DBLACK && !has_red_child(root->lchild))) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }

    //情况三、二
    if (root->rchild->color == BLACK) {
        if (root->rchild->rchild->color != RED) { //RL（情况二）, 经过处理，变成RR处理
            root->rchild->color = RED;
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
        }
        root->rchild->color = root->color; //RR
        root->color = BLACK;
        root->lchild->color -= 1;
        root = left_rotate(root);
        root->rchild->color == BLACK;
    } else {//LR
        if (root->lchild->lchild->color != RED) {
            root->lchild->color = RED;
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK;
        }
        root->lchild->color = root->color; //LL
        root->color = BLACK;
        root->rchild->color -= 1;
        root = right_rotate(root);
        root->lchild->color == BLACK;
    }
    return root;
}

Node *__erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) {
        root->lchild = __erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            Node *temp = predeccessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}


Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) {
        root->lchild = __insert(root->lchild, key);
    } else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    root->color = BLACK;
    return root;
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
    printf("(%d | %d, %d, %d)\n", 
        root->color, 
        root->key, 
        root->lchild->key, 
        root->rchild->key
    );
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 0: root = insert(root, val); break;
            case 1: root = erase(root, val); break;
        }
        output(root);
    }
    return 0;
}


