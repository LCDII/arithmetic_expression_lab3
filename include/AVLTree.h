#pragma once
#include <algorithm>

template <typename T>
struct Node {
    Node* left;
    Node* right;
    T val;
    int height;

    Node() : left(nullptr), right(nullptr), val(), height(0) {}
    Node(const T& _val) : left(nullptr), right(nullptr), val(_val), height(0) {}
};

template <typename T>
class AVLTree {
public:
    Node<T>* root;

    AVLTree() : root(nullptr) {}

    Node<T>* copyTree(Node<T>* cur) {
        if (!cur) return nullptr;

        Node<T>* n = new Node<T>(cur->val);
        n->height = cur->height;
        n->left = copyTree(cur->left);
        n->right = copyTree(cur->right);

        return n;
    }

    void destroy(Node<T>* cur) {
        if (!cur) return;
        destroy(cur->left);
        destroy(cur->right);
        delete cur;
    }

    AVLTree(const AVLTree& other) {
        root = copyTree(other.root);
    }

    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            destroy(root);
            root = copyTree(other.root);
        }
        return *this;
    }

    ~AVLTree() {
        destroy(root);
    }


    int getHeight(Node<T>* cur) const {
        if (cur) return cur->height;
        else return -1;
    }

    void updHeight(Node<T>* cur) {
        if (!cur) return;
        cur->height = 1 + std::max(getHeight(cur->left), getHeight(cur->right));
    }

    int getDiff(Node<T>* cur) const {
        return getHeight(cur->right) - getHeight(cur->left);
    }

    Node<T>* SLRotate(Node<T>* cur) {
        if (!cur || getDiff(cur) < 2 || getDiff(cur->right) < 0) return cur;

        Node<T>* b = cur->right;
        Node<T>* p2 = b->left;

        b->left = cur;
        cur->right = p2;

        updHeight(cur);
        updHeight(b);

        return b;
    }
    Node<T>* SRRotate(Node<T>* cur) {
        if (!cur || getDiff(cur) > -2 || getDiff(cur->left) > 0) return cur;

        Node<T>* b = cur->left;
        Node<T>* p2 = b->right;

        b->right = cur;
        cur->left = p2;

        updHeight(cur);
        updHeight(b);

        return b;
    }

    Node<T>* BLRotate(Node<T>* cur) {
        if (!cur || getDiff(cur) < 2 || getDiff(cur->right) >= 0) return cur;

        cur->right = SRRotate(cur->right);
        return SLRotate(cur);
    }
    Node<T>* BRRotate(Node<T>* cur) {
        if (!cur || getDiff(cur) > -2 || getDiff(cur->left) < 0) return cur;

        cur->left = SLRotate(cur->left);
        return SRRotate(cur);
    }

    Node<T>* rebalance(Node<T>* cur) {
        if (!cur) return cur;

        updHeight(cur);
        int b = getDiff(cur);

        if (b >= 2) {
            if (getDiff(cur->right) < 0)
                return BLRotate(cur);
            else
                return SLRotate(cur);
        }

        if (b <= -2) {
            if (getDiff(cur->left) > 0)
                return BRRotate(cur);
            else
                return SRRotate(cur);
        }

        return cur;
    }

    Node<T>* insert(Node<T>* cur, const T& val) {
        if (!cur) return new Node<T>(val);

        if (val < cur->val) cur->left = insert(cur->left, val);
        else if (val > cur->val) cur->right = insert(cur->right, val);

        return rebalance(cur);
    }

    void insert(const T& val) {
        root = insert(root, val);
    }

    Node<T>* erase(Node<T>* cur, const T& val) { 
        if (!cur) return nullptr;

        if (val < cur->val) {
            cur->left = erase(cur->left, val);
        }
        else if (val > cur->val) {
            cur->right = erase(cur->right, val);
        }
        else {
            if (!cur->left && !cur->right) {
                delete cur;
                return nullptr;
            }
            
            if (!cur->left) {
                Node<T>* tmp = cur->right;
                delete cur;
                return tmp;

            }

            if (!cur->right) {
                Node<T>* tmp = cur->left;
                delete cur;
                return tmp;
            }

            Node<T>* min = cur->right;
            while (min->left) min = min->left;

            cur->val = min->val;
            cur->right = erase(cur->right, min->val);
        }

        return rebalance(cur);
    }

    void erase(const T& val) {
        root = erase(root, val);
    }


};