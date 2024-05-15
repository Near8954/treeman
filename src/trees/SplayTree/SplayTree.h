#ifndef TREEMAN_SPLAYTREE_H
#define TREEMAN_SPLAYTREE_H

#include "../Node.h"
#include "../../header.h"

extern int64_t get_size(Node *t);

void fix_size(Node *t);

void zigzig_right(Node *&t, Node *&q);

void zigzig_left(Node *&t, Node *&q);

void zigzag_right(Node *&t, Node *&q);

void zigzag_left(Node *&t, Node *&q);

void zig_right(Node *&t, Node *&q);

void zig_left(Node *&t, Node *&q);

Node *splay_find(Node *&t, Node *&prev, int64_t num);

bool splay_find(Node *&t, int64_t num);

void Splay(Node *&t, Node *q);

std::pair<Node *, Node *> splay_split(Node *&t, int64_t num);

Node *splay_merge(Node *&t1, Node *&t2);

bool add_splay(Node *&t, int64_t num);

Node* find(Node *t, int x, int y);

void del_splay(Node *&t, int64_t num);

#endif //TREEMAN_SPLAYTREE_H
