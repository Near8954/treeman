#ifndef TREEMAN_NODE_H
#define TREEMAN_NODE_H

struct Node {

    Node() {
        left = nullptr;
        right = nullptr;
    }

    explicit Node(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
    int val{};
    Node *left, *right;
};
#endif //TREEMAN_NODE_H
