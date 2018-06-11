//Private Include
#include "FileInput.h"

//Namespace
using namespace std;

//Private Function Prototypes


//Private Variables

//Implementation
SudokuFile::SudokuFile (std::string const & fileName) {
	mFileName = fileName;
}

SudokuFile::~SudokuFile () {
}

TSudoku SudokuFile::ReadLine (size_t const & index) {

}

bool SudokuFile::VerifyInputFile () {
	return false;
}

void SudokuFile::CreateFileStream () {


}
