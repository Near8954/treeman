#include "SplayTree.h"

int64_t get_size(Node *t) {
    return t ? t->size : 0;
}

void upd(Node *t) {
    t->size = get_size(t->left) + get_size(t->right) + 1;
}

void fix_size(Node *t) {
    if (t == nullptr) {
        return;
    }
    fix_size(t->left);
    fix_size(t->right);
    upd(t);
}


void zigzig_right(Node *&t, Node *&q) {
    Node *p = q->parent;
    Node *g = p->parent;
    Node *qr = q->right;
    Node *pr = p->right;
    Node *root = g->parent;
    g->left = pr;
    if (pr != nullptr) pr->parent = g;
    p->right = g;
    g->parent = p;
    p->left = qr;
    if (qr != nullptr) qr->parent = p;
    q->right = p;
    p->parent = q;
    if (root == nullptr) {
        q->parent = nullptr;
        t = q;
    } else {
        q->parent = root;
        if (root->left == g)
            root->left = q;
        else
            root->right = q;
    }
    return;
}

void zigzig_left(Node *&t, Node *&q) {
    Node *p = q->parent;
    Node *g = p->parent;
    Node *ql = q->left;
    Node *pl = p->left;
    Node *root = g->parent;
    g->right = pl;
    if (pl != nullptr) pl->parent = g;
    p->left = g;
    g->parent = p;
    p->right = ql;
    if (ql != nullptr) ql->parent = p;
    q->left = p;
    p->parent = q;
    if (root == nullptr) {
        t = q;
        q->parent = nullptr;
    } else {
        q->parent = root;
        if (root->left == g)
            root->left = q;
        else
            root->right = q;
    }
    return;
}

void zigzag_right(Node *&t, Node *&q) {
    Node *ql = q->left;
    Node *qr = q->right;
    Node *p = q->parent;
    Node *g = p->parent;
    Node *root = g->parent;
    p->right = ql;
    if (ql != nullptr) ql->parent = p;
    g->left = qr;
    if (qr != nullptr) qr->parent = g;
    q->left = p;
    p->parent = q;
    q->right = g;
    g->parent = q;
    if (root == nullptr) {
        t = q;
        q->parent = nullptr;
    } else {
        q->parent = root;
        if (root->left == g)
            root->left = q;
        else
            root->right = q;
    }
    return;
}

void zigzag_left(Node *&t, Node *&q) {
    Node *ql = q->left;
    Node *qr = q->right;
    Node *p = q->parent;
    Node *g = p->parent;
    Node *root = g->parent;
    p->left = qr;
    if (qr != nullptr) qr->parent = p;
    g->right = ql;
    if (ql != nullptr) ql->parent = g;
    q->left = g;
    g->parent = q;
    q->right = p;
    p->parent = q;
    if (root == nullptr) {
        t = q;
        q->parent = nullptr;
    } else {
        q->parent = root;
        if (root->left == g)
            root->left = q;
        else
            root->right = q;
    }
    return;
}

void zig_right(Node *&t, Node *&q) {
    Node *qr = q->right;
    Node *p = q->parent;
    p->left = qr;
    if (qr != nullptr) qr->parent = p;
    q->right = p;
    p->parent = q;
    q->parent = nullptr;
    t = q;
    return;
}

void zig_left(Node *&t, Node *&q) {
    Node *ql = q->left;
    Node *p = q->parent;
    p->right = ql;
    if (ql != nullptr) ql->parent = p;
    q->left = p;
    p->parent = q;
    q->parent = nullptr;
    t = q;
    return;
}

Node *splay_find(Node *&t, Node *&prev, int64_t num) {
    if (t == nullptr) return prev;
    if (t->val == num) return t;
    if (t->val > num) {
        return splay_find(t->left, t, num);
    } else
        return splay_find(t->right, t, num);
}

bool splay_find(Node *&t, int64_t num) {
    if (t == nullptr) return false;
    if (t->val == num) return true;
    if (t->val > num) {
        return splay_find(t->left, num);
    } else {
        return splay_find(t->right, num);
    }
}

void Splay(Node *&t, Node *q) {
    if (q == nullptr) return;
    if (q->parent == nullptr) return;
    Node *p = q->parent;
    Node *g = p->parent;
    if (g == nullptr) {
        if (p->left == q)
            zig_right(t, q);
        else
            zig_left(t, q);
    } else {
        if (p->left == q && g->left == p)
            zigzig_right(t, q);
        else if (p->right == q && g->right == p)
            zigzig_left(t, q);
        else if (p->right == q && g->left == p)
            zigzag_right(t, q);
        else if (p->left == q && g->right == p)
            zigzag_left(t, q);
        Splay(t, q);
    }
    return;
}

std::pair<Node *, Node *> splay_split(Node *&t, int64_t num) {
    Node *nll = nullptr;
    Node *q = splay_find(t, nll, num);
    if (q != nullptr) {
        Splay(t, q);
        if (t->val >= num) {
            Node *t1 = t->left;
            t->left = nullptr;
            if (t1 != nullptr) t1->parent = nullptr;
            return {t1, t};
        } else {
            Node *t2 = t->right;
            t->right = nullptr;
            if (t2 != nullptr) t2->parent = nullptr;
            return {t, t2};
        }
    }
    return {nullptr, nullptr};
}

Node *splay_merge(Node *&t1, Node *&t2) {
    Node *q = t2;
    while (q != nullptr && q->left != nullptr) {
        q = q->left;
    }
    Splay(t2, q);
    if (t2 != nullptr) {
        t2->left = t1;
        if (t1 != nullptr) t1->parent = t2;
        return t2;
    }
    return t1;
}

bool add_splay(Node *&t, int64_t num) {
    std::pair<Node *, Node *> sp = splay_split(t, num);
    if (sp.second == nullptr || sp.second->val != num) {
        Node *q = new Node;
        q->val = num;
        //q->nd.wt = -1;
        q->color = false;
        q->left = nullptr;
        q->right = nullptr;
        q->parent = nullptr;
        q->left = sp.first;
        if (sp.first != nullptr) sp.first->parent = q;
        q->right = sp.second;
        if (sp.second != nullptr) sp.second->parent = q;
        t = q;
        return true;
    }
    return false;
}

void del_splay(Node *&t, int64_t num) {
    Node *nll = nullptr;
    Node *q = splay_find(t, nll, num);
    Splay(t, q);
    Node *r = t->right;
    Node *l = t->left;
    Node *tmp = t;
    if (l != nullptr) l->parent = nullptr;
    if (r != nullptr) r->parent = nullptr;
    t = splay_merge(l, r);
    delete tmp;
}

Node* find(Node *node, int x, int y) {
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