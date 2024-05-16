#ifndef TREEMAN_RBTREE_H
#define TREEMAN_RBTREE_H

#include "../../header.h"
#include "../Node.h"

class RBTree {
public:
    RBTree();

    void insert(int64_t key);

    void remove(int64_t key);

    Node *search(int64_t key);

    Node* find(int x, int y);

    Node *get_root() {
        return root;
    }

private:
    Node *root;

    Node *insert(Node *&node, int64_t key);

    void insertFix(Node *&node);

    void rotateLeft(Node *&node);

    void rotateRight(Node *&node);

    Node *remove(Node *&root, int64_t key);

    void removeFix(Node *&node);

    Node *findMin(Node *&node);

    Node *search(Node *&node, int64_t key);

    Node *find(Node *&node, int x, int y);
};

#endif //TREEMAN_RBTREE_H
