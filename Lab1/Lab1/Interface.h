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
	void consol_intface();	// виклик консольного інтерфейсу програми
private:
	Puzzle read_puzzle();					// зчитування пазлу від користувача з консолі
	void write_puzzle(Puzzle puzzle);		// запис пазлу на консоль
	void write_solution(Algorithm& algo);	// виведення розв'язку пазлу (послідовні стани розв'язку від початкового до кінечного)
};

