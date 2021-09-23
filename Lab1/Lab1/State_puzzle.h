#pragma once
#include "Puzzle.h"
struct State_puzzle			// стан пазла
{
	Puzzle puzzle;		// поточний стан
	int index_father;	// індекс попереднього стану в списку 
	State_puzzle(Puzzle p, int ind_fa)
	{
		puzzle = p;
		index_father = ind_fa;
	}
};

