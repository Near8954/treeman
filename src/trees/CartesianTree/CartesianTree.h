//
// Created by near on 5/13/24.
//
#include "../../header.h"

#ifndef TREEMAN_CARTESIANTREE_H
#define TREEMAN_CARTESIANTREE_H

struct CartesianNode {
    int64_t priority;
    int64_t val;
    int64_t size;
    int64_t x, y;
    CartesianNode *left;
    CartesianNode *right;

    CartesianNode(int64_t key);
};


class CartesianTree {
private:
    CartesianNode *root;

    CartesianNode *merge(CartesianNode *l, CartesianNode *r) {
        if (l == nullptr) {
            return r;
        }
        if (r == nullptr) {
            return l;
        }
        if (l->priority < r->priority) {
            l->right = merge(l->right, r);
            upd(l);
            return l;
        }
        r->left = merge(l, r->left);
        upd(r);
        return r;
    }

    int64_t get_size(CartesianNode* t) {
        return  t ? t->size : 0;
    }

    void upd(CartesianNode* nd) {
        if (nd == nullptr) {
            return;
        }
        nd->size = get_size(nd->left) + get_size(nd->right) + 1;
    }

    std::pair<CartesianNode *, CartesianNode *> split(CartesianNode *vx, int64_t k) { // [< k] [>= k]
        if (vx == nullptr) {
            return {nullptr, nullptr};
        }
        if (vx->val < k) {
            auto tmp = split(vx->right, k);
            vx->right = tmp.first;
            upd(vx);
            upd(tmp.second);
            return {vx, tmp.second};
        }
        auto tmp = split(vx->left, k);
        vx->left = tmp.second;
        upd(vx);
        upd(tmp.first);
        return {tmp.first, vx};
    }

    bool exist(int64_t k) {
        if (root == nullptr) {
            return false;
        }
        auto tmp_left = split(root, k); // [< k], [>= k]
        auto tmp_right = split(tmp_left.second, k + 1); // [= k], [> k]
        bool result = (tmp_right.first != nullptr);
        root = merge(tmp_left.first, merge(tmp_right.first, tmp_right.second));
        return result;
    }

    int64_t find_min(CartesianNode *vx) {
        if (vx == nullptr) {
            return -1;
        }
        return vx->left == nullptr ? vx->val : find_min(vx->left);
    }

    void clear(CartesianNode *vx) {
        if (vx->left != nullptr) {
            clear(vx->left);
        }
        if (vx->right != nullptr) {
            clear(vx->right);
        }
        delete vx;
    }

public:
    CartesianTree() : root(nullptr) {}

    void insert(int64_t k);

    void remove(int64_t k);

    CartesianNode* find(int x, int y);

    CartesianNode* find(CartesianNode* root, int x, int y);

    ~CartesianTree() {
        clear(root);
    }

    bool exists(int64_t k) {
        return exist(k);
    }

    CartesianNode *get_root() {
        return root;
    }

    CartesianNode *get_right() {
        return root->right;
    }

    CartesianNode *get_left() {
        return root->left;
    }
};

#endif //TREEMAN_CARTESIANTREE_H
