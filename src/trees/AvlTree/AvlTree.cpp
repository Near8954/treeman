#include "AvlTree.h"

int height(Node *node) {
    return node ? node->height : 0;
}

int is_balance(Node *node) {
    return height(node->right) - height(node->left);
}

void update_height(Node *node) {
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

Node *rotate_right(Node *&node) {
    Node *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    update_height(node);
    update_height(new_root);
    return new_root;
}

Node *left_rotate(Node *&node) {
    Node *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    update_height(node);
    update_height(new_root);
    return new_root;
}

Node *balance(Node *&p) // балансировка узла p
{
    update_height(p);
    if (is_balance(p) == 2) {
        if (is_balance(p->right) < 0)
            p->right = rotate_right(p->right);
        return left_rotate(p);
    }
    if (is_balance(p) == -2) {
        if (is_balance(p->left) > 0)
            p->left = left_rotate(p->left);
        return rotate_right(p);
    }
    return p; // балансировка не нужна
}

Node *AvlTree::insert(Node *&p, int64_t k) // вставка ключа k в дерево с корнем p
{
    if (!p) return new Node(k);
    if (k < p->val)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

void AvlTree::insert(int64_t key) {
    root = insert(root, key);
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* removemin(Node* p)
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

Node *AvlTree::remove(Node *&p, int64_t k) {
    if (!p) return 0;
    if (k < p->val)
        p->left = remove(p->left, k);
    else if (k > p->val)
        p->right = remove(p->right, k);
    else
    {
        Node *q = p->left;
        Node *r = p->right;
        delete p;
        if (!r) return q;
        Node *min = minValueNode(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void AvlTree::remove(int64_t key) {
    root = remove(root, key);
}

Node *AvlTree::search(Node *&node, int64_t key) {
    // Base Cases: root is null or key is present at root
    if (node == nullptr || node->val == key)
        return node;

    // Key is greater than root's key
    if (node->val < key)
        return search(node->right, key);

    // Key is smaller than root's key
    return search(node->left, key);
}

Node *AvlTree::search(int64_t key) {
    return search(root, key);
}

AvlTree::AvlTree() {
    root = nullptr;
}

Node *AvlTree::find(int x, int y) {
    return find(root, x, y);
}

Node *AvlTree::find(Node *&node, int x, int y) {
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
