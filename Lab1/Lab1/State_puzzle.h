#pragma once
#include "Puzzle.h"
struct State_puzzle			// ���� �����
{
	Puzzle puzzle;		// �������� ����
	int index_father;	// ������ ������������ ����� � ������ 
	State_puzzle(Puzzle p, int ind_fa)
	{
		puzzle = p;
		index_father = ind_fa;
	}
};

