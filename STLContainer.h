#pragma once
#include <map>
#include <iostream>
#include "Exp_contr.h"
using namespace std;

template<typename T>
class STLContainer
{
public:
    // Iterator class nested inside container
    class Iterator
    {
    private:
        typename map<int, T*>::iterator it;
        map<int, T*>* container;

    public:
        // Constructor
        Iterator(typename map<int, T*>::iterator iterator, map<int, T*>* cont)
            : it(iterator), container(cont) {}

        // Copy constructor
        Iterator(const Iterator& other)
            : it(other.it), container(other.container) {}

        // Assignment operator
        Iterator& operator=(const Iterator& other)
        {
            if (this != &other)
            {
                it = other.it;
                container = other.container;
            }
            return *this;
        }

        // Pre-increment operator (++it)
        Iterator& operator++()
        {
            ++it;
            return *this;
        }

        // Post-increment operator (it++)
        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++it;
            return temp;
        }

        // Pre-decrement operator (--it)
        Iterator& operator--()
        {
            --it;
            return *this;
        }

        // Post-decrement operator (it--)
        Iterator operator--(int)
        {
            Iterator temp = *this;
            --it;
            return temp;
        }

        // Dereference operator (*it)
        pair<const int, T*>& operator*()
        {
            return *it;
        }

        // Arrow operator (it->)
        pair<const int, T*>* operator->()
        {
            return &(*it);
        }

        // Equality operator (==)
        bool operator==(const Iterator& other) const
        {
            return it == other.it;
        }

        // Inequality operator (!=)
        bool operator!=(const Iterator& other) const
        {
            return it != other.it;
        }

        // Get underlying iterator
        typename map<int, T*>::iterator getIterator() const
        {
            return it;
        }
    };

private:
    map<int, T*> container;
    int nextId;

public:
    STLContainer() : nextId(1) {}
    
    ~STLContainer()
    {
        clear();
    }

    // Add element to container
    int add(T* element)
    {
        if (element == nullptr)
        {
            throw ContainerException(100, "Cannot add null pointer to container");
        }
        int id = nextId++;
        container[id] = element;
        return id;
    }

    // View element by key
    T* view(int key) const
    {
        auto it = container.find(key);
        if (it == container.end())
        {
            throw ContainerException(101, "Key " + to_string(key) + " not found in container");
        }
        return it->second;
    }

    // Delete element by key
    void remove(int key)
    {
        auto it = container.find(key);
        if (it == container.end())
        {
            throw ContainerException(102, "Key " + to_string(key) + " not found in container");
        }
        delete it->second;
        container.erase(it);
    }

    // Get iterator to beginning
    Iterator begin()
    {
        return Iterator(container.begin(), &container);
    }

    // Get iterator to end
    Iterator end()
    {
        return Iterator(container.end(), &container);
    }

    // Check if container is empty
    bool isEmpty() const
    {
        return container.empty();
    }

    // Get size of container
    size_t size() const
    {
        return container.size();
    }

    // Clear all elements
    void clear()
    {
        for (auto& pair : container)
        {
            delete pair.second;
        }
        container.clear();
        nextId = 1;
    }

    // Get all keys
    void getAllKeys(map<int, T*>& result) const
    {
        result = container;
    }
};
