#ifndef QUEUENODE_H
#define QUEUENODE_H

template <typename T>
class QueueNode {
public:
	T data;
	QueueNode<T>* next;

	QueueNode(const T& data) : data(data), next(nullptr) {}
};

#endif