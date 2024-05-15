#include "AvlTree.h"

int height(Node *node) {
    return node ? node->height : 0;
}

int balance(Node *node) {
    return height(node->right) - height(node->left);
}

void update_height(Node *node) {
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

Node *rotate_right(Node *node) {
    Node *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    update_height(node);
    update_height(new_root);
    return new_root;
}

Node *left_rotate(Node *node) {
    Node *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    update_height(node);
    update_height(new_root);
    return new_root;
}

Node *big_right_rotate(Node *node) {
    node->right = left_rotate(node->right);
    return rotate_right(node);
}

Node *big_left_rotate(Node *node) {
    node->left = rotate_right(node->left);
    return left_rotate(node);
}

Node *AvlTree::insert(Node *node, int64_t key) {
    // 1. Perform the normal BST insertion
    if (node == nullptr)
        return new Node(key);

    if (key < node->val)
        node->left = insert(node->left, key);
    else if (key > node->val)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    // 2. Update height of this ancestor node
    update_height(node);

    // 3. Get the balance factor
    int balance_factor = balance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance_factor < -1 && key < node->left->val)
        return rotate_right(node);

    // Right Right Case
    if (balance_factor > 1 && key > node->right->val)
        return left_rotate(node);

    // Left Right Case
    if (balance_factor < -1 && key > node->left->val) {
        big_right_rotate(node);
    }

    // Right Left Case
    if (balance_factor > 1 && key < node->right->val) {
        big_left_rotate(node);
    }

    // return the (unchanged) node pointer
    return node;
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

Node *AvlTree::remove(Node *root, int64_t key) {
    // 1. Perform the normal BST deletion
    if (root == nullptr)
        return root;

    if (key < root->val)
        root->left = remove(root->left, key);
    else if (key > root->val)
        root->right = remove(root->right, key);
    else {
        // node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node *temp = root->left ? root->left : root->right;
            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            delete temp;
        } else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node *temp = minValueNode(root->right);
            // Copy the inorder successor's data to this node
            root->val = temp->val;
            // Delete the inorder successor
            root->right = remove(root->right, temp->val);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
        return root;

    // 2. Update height of this ancestor node
    update_height(root);

    // 3. Get the balance factor
    int balance_factor = balance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance_factor < -1 && balance(root->left) <= 0)
        return rotate_right(root);

    // Right Right Case
    if (balance_factor > 1 && balance(root->right) >= 0)
        return left_rotate(root);

    // Left Right Case
    if (balance_factor < -1 && balance(root->left) > 0) {
        root->left = left_rotate(root->left);
        return rotate_right(root);
    }

    // Right Left Case
    if (balance_factor > 1 && balance(root->right) < 0) {
        root->right = rotate_right(root->right);
        return left_rotate(root);
    }

    return root;
}

void AvlTree::remove(int64_t key) {
    root = remove(root, key);
}

Node *AvlTree::search(Node *node, int64_t key) {
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

Node *AvlTree::find(Node *node, int x, int y) {
    if (node == nullptr || (node->x == x && node->y == y)) {
        return node;
    }
    if (node->x < x) {
        return find(node->right, x, y);
    }
    if (node->x > x) {
        return find(node->left, x, y);
    }
}
