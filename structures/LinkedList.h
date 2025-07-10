#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~LinkedList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void push_back(const T& value) {
        Node* node = new Node(value);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        count++;
    }

    void clear() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        count = 0;
    }

    int size() const { return count; }

    void printAll(std::function<void(const T&)> printer) const {
        Node* curr = head;
        while (curr) {
            printer(curr->data);
            curr = curr->next;
        }
    }
};

#endif // LINKEDLIST_H