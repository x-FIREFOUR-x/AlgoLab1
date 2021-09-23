#pragma once
#pragma once
#include <vector>
#include "State_puzzle.h"

using namespace std;
class Test
{
	int amount_iterations;
	int amount_state;
public:
	Test();
	int get_iterations();
	int get_state();

	void increase_iter(int numb = 1);
	void count_states(vector<State_puzzle>& states);
};
