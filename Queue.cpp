#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "Queue.h"

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        this->clearQueue();
        QueueNode<T>* current = other.front;
        while (current != nullptr) {
            this->enqueue(current->data);
            current = current->next;
        }
    }
    return *this;
}


template <typename T>
void Queue<T>::enqueue(const T& value) {
    QueueNode<T>* newNode = new QueueNode<T>(value);

    if (this->isEmpty())
    {
        this->front = newNode;
        this->rear = newNode;
    }
    else
    {
        this->rear->next = newNode;
        this->rear = newNode;
    }
}

template <typename T>
void Queue<T>::dequeue()
{
    if (this->isEmpty()) { return; }
    QueueNode<T>* temp = this->front;
    this->front = this->front->next;
    if (this->front == nullptr) { this->rear = nullptr; }
    delete temp;
}

template <typename T>
T& Queue<T>::getFront() { return this->front->data; }

template <typename T>
bool Queue<T>::isEmpty() const { return this->front == nullptr; }

template <typename T>
int Queue<T>::getSize() const
{
    int size = 0;
    QueueNode<T>* curr = this->front;
    while (curr != nullptr) {
        size++;
        curr = curr->next;
    }
    return size;
}

template <typename T>
void Queue<T>::display() const
{
    if (this->isEmpty()) { return; }
    QueueNode<T>* current = this->front;
    while (current != NULL)
    {
        cout << current->data;
        current = current->next;
    }
    cout << endl;
}

template <typename T>
template <typename Predicate>
Queue<T> Queue<T>::find(Predicate pred) const
{
    Queue<T> result;
    QueueNode<T>* current = this->front;
    while (current != nullptr)
    {
        if (pred(current->data)) { result.enqueue(current->data); }
        current = current->next;
    }
    return result;
}


template <typename T>
template <typename Compare>
void Queue<T>::sort(Compare comp) 
{
    if (this->isEmpty() || this->front->next == nullptr) return;
    bool swapped;
    do {
        swapped = false;
        QueueNode<T>* current = this->front;
        while (current->next != nullptr) 
        {
            if (comp(*(current->next->data), *(current->data))) 
            {
                swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

#endif