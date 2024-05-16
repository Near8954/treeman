//
// Created by near on 5/16/24.
//

#include "RBTree.h"

extern void update_height(Node *node);

void RBTree::insert(int64_t key) {
    Node *newNode = new Node(key);
    newNode->color = true;
    Node *y = nullptr;
    Node *x = this->root;

    while (x != nullptr) {
        y = x;
        if (newNode->val < x->val)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;
    if (y == nullptr)
        this->root = newNode;
    else if (newNode->val < y->val)
        y->left = newNode;
    else
        y->right = newNode;
    insertFix(newNode);
}

void RBTree::insertFix(Node *&node) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;

    while ((node != this->root) && node->color &&
           node->parent->color) {

        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {

            Node *uncle = grandparent->right;
            if (uncle != nullptr && uncle->color) { // красный дядя и мы слева
                grandparent->color = true;
                parent->color = false;
                uncle->color = false;
                node = grandparent;
            } else {
                // мы справа
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                // мы слева
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
            // папа правый ребенок деда
        else {
            Node *uncle = grandparent->left;
            // дядя красный
            if ((uncle != nullptr) && (uncle->color == true)) {
                grandparent->color = true;
                parent->color = false;
                uncle->color = false;
                node = grandparent;
            } else {
                // мы левый ребенок
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                // мы правый ребенок
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }

    this->root->color = false;
}

RBTree::RBTree() {
    root = nullptr;
}

void RBTree::remove(int64_t key) {
    Node *node = search(root, key);
    Node *x = nullptr, *y = nullptr;

    if (!node) {
        return;
    }

    if (node->left == nullptr || node->right == nullptr) {
        y = node;
    } else {
        y = findMin(node);
    }

    if (y->left != nullptr) {
        x = y->left;
    } else {
        x = y->right;
    }

    if (x != nullptr) {
        x->parent = y->parent;
    }

    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != node) {
        node->val = y->val;
    }

    if (!y->color) {
        removeFix(x);
    }

    delete y;
}

void RBTree::removeFix(Node *&node) {
    Node *s;
    while (node != root && !node->color) {
        if (node == node->parent->left) {
            s = node->parent->right;
            if (s->color) {
                s->color = false;
                node->parent->color = true;
                rotateLeft(node->parent);
                s = node->parent->right;
            }

            if (!s->right->color && !s->left->color) {
                s->color = true;
                node = node->parent;
            } else {
                if (!s->right->color) {
                    s->left->color = false;
                    s->color = true;
                    rotateRight(s);
                    s = node->parent->right;
                }

                s->color = node->parent->color;
                node->parent->color = false;
                s->right->color = false;
                rotateLeft(node->parent);
                node = root;
            }
        } else {
            s = node->parent->left;
            if (s->color) {
                s->color = false;
                node->parent->color = true;
                rotateRight(node->parent);
                s = node->parent->left;
            }

            if (!s->left->color && !s->right->color) {
                s->color = true;
                node = node->parent;
            } else {
                if (!s->left->color) {
                    s->right->color = false;
                    s->color = true;
                    rotateLeft(s);
                    s = node->parent->left;
                }

                s->color = node->parent->color;
                node->parent->color = false;
                s->left->color = false;
                rotateRight(node->parent);
                node = root;
            }
        }
    }
    node->color = false;
}

Node *RBTree::findMin(Node *&node) {
    Node *temp = node;

    while (temp->left != nullptr)
        temp = temp->left;

    return temp;
}

Node *RBTree::search(int64_t key) {
    return search(root, key);
}

Node *RBTree::search(Node *&node, int64_t key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->val == key) {
        return node;
    }
    if (node->val < key) {
        return search(node->right, key);
    }
    return search(node->left, key);
}

void RBTree::rotateLeft(Node *&node) {
    Node *new_root = node->right;
    node->right = new_root->left;

    if (node->right != nullptr)
        node->right->parent = node;

    new_root->parent = node->parent;

    if (node->parent == nullptr)
        root = new_root;
    else if (node == node->parent->left)
        node->parent->left = new_root;
    else
        node->parent->right = new_root;

    new_root->left = node;
    node->parent = new_root;
}

void RBTree::rotateRight(Node *&node) {
    Node *new_root = node->left;
    node->left = new_root->right;

    if (node->left != nullptr)
        node->left->parent = node;

    new_root->parent = node->parent;

    if (node->parent == nullptr)
        root = new_root;
    else if (node == node->parent->left)
        node->parent->left = new_root;
    else
        node->parent->right = new_root;

    new_root->right = node;
    node->parent = new_root;
}

Node *RBTree::find(Node *&node, int x, int y) {
    if (node == nullptr || ((node->x <= x) && (x <= node->x + 80) && node->y <= y && y <= node->y + 80)) {
        return node;
    }
    if (node->x < x) {
        return find(node->right, x, y);
    }
    if (node->x > x) {
        return find(node->left, x, y);
    }
}

Node *RBTree::find(int x, int y) {
    return find(root, x, y);
}
