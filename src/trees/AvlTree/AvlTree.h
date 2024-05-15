//
// Created by near on 5/15/24.
//

#ifndef TREEMAN_AVLTREE_H
#define TREEMAN_AVLTREE_H

#include "../Node.h"

class AvlTree {
public:
    AvlTree();

    void insert(int64_t key);

    void remove(int64_t key);

    Node *search(int64_t key);

    Node* find(int x, int y);

    Node *get_root() {
        return root;
    }

private:
    Node *root;

    Node *insert(Node *node, int64_t key);

    Node *remove(Node *root, int64_t key);

    Node *search(Node *node, int64_t key);

    Node* find(Node* node, int x, int y);
};

#endif //TREEMAN_AVLTREE_H
