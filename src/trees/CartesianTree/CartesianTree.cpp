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

CartesianNode *CartesianTree::find(CartesianNode *root, int x, int y) {
    if (root == nullptr || root->x == x && root->y == y) {
        return root;
    }
    if (root->x > x) {
        return find(root->left, x, y);
    }
    return find(root->right, x, y);
}

