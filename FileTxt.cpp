#include "FileTxt.h"
#include "Exp_file.h"
#include <sstream>

using namespace std;

template <typename T>
void FileTxt<T>::save(const T& object) {
    fstream file;
    openFile(file, ios::out | ios::app);
    if (file.is_open()) {
        object.saveTextRecord(file);
        file << "\n";
        file.close();
    }
}

template <typename T>
Queue<T*> FileTxt<T>::read() {
    Queue<T*> queue;
    fstream file;
    openFile(file, ios::in);

    if (!file.is_open()) {
        return queue;
    }

    while (file.peek() != EOF && !file.eof()) {
        T* object = new T();
        try {
            object->loadFromText(file);
            if (file.fail() && !file.eof()) {
                delete object;
                break;
            }
            queue.enqueue(object);
        }
        catch (...) {
            delete object;
            if (file.eof()) {
                break;
            }
        }
    }

    file.close();
    return queue;
}

template <typename T>
void FileTxt<T>::clearFile() const {
    ofstream file(filename, ios::out | ios::trunc);
}

template <typename T>
void FileTxt<T>::openFile(fstream& file, ios_base::openmode mode) const {
    file.open(filename, mode);
    if (!file.is_open()) {
        throw FileException(50, "Failed to open file: " + filename);
    }
}

template <typename T>
void FileTxt<T>::saveSTLContainer(STLContainer<T>& container) {
    fstream file;
    openFile(file, ios::out | ios::app);
    if (file.is_open()) {
        for (typename STLContainer<T>::Iterator it = container.begin(); it != container.end(); ++it) {
            if ((*it).second) {
                (*it).second->saveTextRecord(file);
                file << "\n";
            }
        }
        file.close();
    }
}

template <typename T>
void FileTxt<T>::loadSTLContainer(STLContainer<T>& container) {
    fstream file;
    openFile(file, ios::in);

    if (!file.is_open()) {
        return;
    }

    while (file.peek() != EOF && !file.eof()) {
        T* object = new T();
        try {
            object->loadFromText(file);
            if (file.fail() && !file.eof()) {
                delete object;
                break;
            }
            container.add(object);
        }
        catch (const ContainerException& e) {
            delete object;
            throw; // Re-throw ContainerException
        }
        catch (...) {
            delete object;
            if (file.eof()) {
                break;
            }
        }
    }

    file.close();
}

