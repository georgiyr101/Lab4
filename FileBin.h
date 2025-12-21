#ifndef FILE_BIN
#define FILE_BIN

#include "File.h"
#include "Queue.h"
#include "STLContainer.h"

template <typename T>
class FileBin :public File
{
public:
    FileBin(const std::string& fname) : File(fname) {}
    ~FileBin() = default;

    void save(const T& object);
    Queue<T*> read();
    void clearFile() const;
    void openFile(fstream& file, ios_base::openmode mode) const;

    // STL Container methods
    void saveSTLContainer(STLContainer<T>& container);
    void loadSTLContainer(STLContainer<T>& container);
};

#endif


