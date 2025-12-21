#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

class File
{
protected:
	std::string filename;
	std::ifstream iFile;
	std::ofstream oFile;
	std::fstream fFile;
public:
	explicit File(const std::string& fname) : filename(fname) {}
	virtual ~File();
};

#endif
