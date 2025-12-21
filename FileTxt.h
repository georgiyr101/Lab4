#ifndef FILE_TXT
#define FILE_TXT

#include "File.h"
#include "Queue.h"
#include "STLContainer.h"

template <typename T>
class FileTxt :public File
{
public:
	FileTxt(const string& filename) : File(filename) {}
	~FileTxt() = default;

	void save(const T& obj);
	void clearFile() const;
	Queue<T*> read();
	void openFile(std::fstream& file, std::ios_base::openmode mode) const;

	// STL Container methods
	void saveSTLContainer(STLContainer<T>& container);
	void loadSTLContainer(STLContainer<T>& container);
};

#endif FILE_TXT

