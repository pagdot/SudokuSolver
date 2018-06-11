#ifndef FILEINPUT_H
#define FILEINPUT_H

#include <string>
#include <fstream>

#include "Defines.h"

class SudokuFile{
public:

	SudokuFile(std::string const & fileName);
	~SudokuFile();

	TSudoku ReadLine (size_t const & index = 0);

private:
	bool VerifyInputFile ();
	void CreateFileStream ();

	std::ifstream mFile;
	std::string mFileName;
};






#endif