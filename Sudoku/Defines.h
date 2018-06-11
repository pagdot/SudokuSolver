#ifndef DEFINES_H
#define DEFINES_H

//System Includes
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <array>
#include <list>

//Varibale declarations
static const size_t base = 3;


//Type declarations
typedef std::array<std::array<size_t, base*base>, base*base> TSudoku;
typedef std::list<size_t> TSudokuField;
typedef std::array<std::array<TSudokuField, base*base>, base*base> TSudokuFields;






#endif