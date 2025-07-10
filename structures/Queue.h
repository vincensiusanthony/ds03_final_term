#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* front;
    Node* back;

public:
    Queue() : front(nullptr), back(nullptr) {}

    ~Queue() {
        while (!isEmpty()) dequeue();
    }

    void enqueue(const T& item) {
        Node* node = new Node(item);
        if (back) back->next = node;
        back = node;
        if (!front) front = node;
    }

    T dequeue() {
        if (isEmpty()) throw std::out_of_range("Queue is empty");
        Node* temp = front;
        T data = temp->data;
        front = front->next;
        if (!front) back = nullptr;
        delete temp;
        return data;
    }

    T peek() const {
        if (isEmpty()) throw std::out_of_range("Queue is empty");
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }
};

#endif // QUEUE_H