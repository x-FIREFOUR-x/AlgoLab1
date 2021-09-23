#pragma once
#include <chrono>
#include <time.h>
#include <ctime>
#include <stack>

#include"Algorithm.h"
#include "Puzzle.h"

using namespace std;
class Interface
{
public:
	void consol_intface();
private:
	Puzzle read_puzzle();
	void write_puzzle(Puzzle puzzle);
	void write_solution(Algorithm& algo);
};

