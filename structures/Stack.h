#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) pop();
    }

    void push(const T& item) {
        Node* node = new Node(item);
        node->next = top;
        top = node;
    }

    T pop() {
        if (isEmpty()) throw std::out_of_range("Stack is empty");
        Node* temp = top;
        T data = temp->data;
        top = top->next;
        delete temp;
        return data;
    }

    T peek() const {
        if (isEmpty()) throw std::out_of_range("Stack is empty");
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};

#endif // STACK_H