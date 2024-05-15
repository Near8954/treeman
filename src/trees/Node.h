#pragma once
#ifndef TREEMAN_NODE_H
#define TREEMAN_NODE_H

#include "../header.h"

struct Node {

    Node() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    explicit Node(int64_t x) {
        val = x;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        size = 1;
        height = 1;
    }

    int64_t val{};
    int64_t size{};
    int height{};
    bool color;
    Node *left, *right, *parent;
    int64_t x, y;
};

#endif //TREEMAN_NODE_H
