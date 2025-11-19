#ifndef QUEUENODE_H
#define QUEUENODE_H

template <typename T>
class QueueNode
{
public:
    T data;
    QueueNode<T>* next;

    QueueNode() : data(), next(nullptr) {}
    QueueNode(const T& value) : data(value), next(nullptr) {}
    QueueNode(const T& value, QueueNode<T>* nextNode) : data(value), next(nextNode) {}
    ~QueueNode() {}
};

#endif