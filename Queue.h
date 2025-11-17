#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "QueueNode.h"
using namespace std;

template <typename T>
struct QueueNode
{
    T data;
    QueueNode<T>* next;
};

template <typename T>
class Queue
{
private:
    QueueNode<T>* front;
    QueueNode<T>* rear;

public:
    Queue()
    {
        this->front = nullptr;
        this->rear = nullptr;
    }

    Queue(const Queue& other)
    {
        this->front = nullptr;
        this->rear = nullptr;
        QueueNode<T>* current = other.front;
        while (current != nullptr)
        {
            enqueue(current->data);
            current = current->next;
        }
    }

    ~Queue() {}
    Queue& operator=(const Queue& other);

    void enqueue(const T& value);
    void dequeue();
    T& getFront();
    bool isEmpty() const;
    int getSize() const;
    void display() const;


    Queue<T> find(const T& value) const;
    void sort();
};

#include "Queue.cpp"
#endif