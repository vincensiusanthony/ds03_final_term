#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>
#include "../models/Book.h"

class BST {
private:
    struct Node {
        Book data;
        Node* left;
        Node* right;
        Node(const Book& b) : data(b), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* insert(Node* node, const Book& book) {
        if (!node) return new Node(book);
        if (book.title < node->data.title)
            node->left = insert(node->left, book);
        else
            node->right = insert(node->right, book);
        return node;
    }

    void inOrder(Node* node, std::function<void(const Book&)> visit) const {
        if (!node) return;
        inOrder(node->left, visit);
        visit(node->data);
        inOrder(node->right, visit);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() { clear(root); }

    void insert(const Book& book) {
        root = insert(root, book);
    }

    void inOrder(std::function<void(const Book&)> visit) const {
        inOrder(root, visit);
    }
};

#endif // BST_H