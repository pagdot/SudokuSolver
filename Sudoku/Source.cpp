#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <array>
#include <list>

static const size_t base = 3;
typedef std::array<std::array<size_t, base*base>, base*base> TSudoku;
typedef std::list<size_t> TSudokuField;
typedef std::array<std::array<TSudokuField, base*base>, base*base> TSudokuFields;

bool solveSudoku(TSudoku &s);
void updateField(TSudoku &s, TSudokuFields &sf, size_t row, size_t col);
void updateAll(TSudoku& s, TSudokuFields& sf);
void printSudoku(TSudoku& const s);

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << "<file>" << std::endl;
		return -1;
	}

	std::ifstream in(argv[1]);
	if (!in.good()) {
		std::cout << "Can't open file: " << argv[1] << std::endl;
		return -2;
	}

	TSudoku s;
	for (auto& r : s) {
		for (auto& c : r) {
			char ch;
			if (!in.get(ch)) {
				std::cout << "Input file too short" << std::endl;
				return -3;
			}
			c = ch-'0';
		}
	}
	in.close();

	solveSudoku(s);
}

bool solveSudoku(TSudoku & s) {
	TSudokuFields sf;
	printSudoku(s);
	updateAll(s, sf);
	std::cout << std::endl;
	std::cout << "==============================================" << std::endl;
	std::cout << std::endl;

	printSudoku(s);

	return false;
}

void updateAll(TSudoku& s, TSudokuFields& sf) {
	for (size_t i = 0; i < s.size(); i++) {
		for (size_t j = 0; j < s.size(); j++) {
			if (s[i][j] == 0) {
				updateField(s, sf, i, j);
				if (sf[i][j].size() == 1) {
					s[i][j] = *(sf[i][j].cbegin());
					sf[i][j].clear();
					updateAll(s, sf);
					return;
				}
			}
		}
	}
}

void printSudoku(TSudoku& s) {
	for (auto const &row : s) {
		for (auto const f : row) {
			std::cout << f << " ";
		}
		std::cout << std::endl;
	}
}

void updateField(TSudoku& s, TSudokuFields& sf, size_t row, size_t col) {
	TSudokuField const initF = { 1,2,3,4,5,6,7,8,9 };
	TSudokuField &f = sf[row][col];
	if (f.empty()) f = initF;

	auto it = f.begin();
	while (it != f.end()) {
		//check column
		if (std::find_if(s.cbegin(), s.cend(), [&](auto const &line) {
			return line[col] == *it;
			}) != s.cend()) {
			auto old = it++;
			f.erase(old);
		//check row
		} else if (std::find_if(s[row].cbegin(), s[row].cend(), [&](auto const field) {
			return field == *it;
			}) != s[row].cend()) {
			auto old = it++;
			f.erase(old);
		//check square (base x base)
		} else {
			size_t startRow = row - row % base;
			size_t startCol = col - col % base;
			bool found = false;
			for (size_t i = startRow ; (i < startRow+base) && (!found); ++i) {
				for (size_t j = startCol; (j < startCol + base) && (!found); ++j) {
					if (s[i][j] == *it) {
						found = true;
					}
				}
			}

			if (found) {
				auto old = it++;
				f.erase(old);
			} else {
				++it;
			}
		}
	}


}
