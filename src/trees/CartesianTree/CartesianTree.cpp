#include "CartesianTree.h"
std::mt19937 rnd(47);


CartesianNode::CartesianNode(int64_t key): priority(rnd()), val(key), left(nullptr), right(nullptr), size(1) { }

void CartesianTree::insert(int64_t k) {
    if (exist(k)) {
        return;
    }
    auto tmp = split(root, k);
    root = merge(tmp.first, merge(new CartesianNode(k), tmp.second));
}

void CartesianTree::remove(int64_t k) {
    if (!exists(k)) {
        return;
    }
    auto tmp = split(root, k);
    root = merge(tmp.first, split(tmp.second, k + 1).second);
}

CartesianNode *CartesianTree::find(int x, int y) {
    return find(root, x, y);
}

CartesianNode *CartesianTree::find(CartesianNode *node, int x, int y) {
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

