#pragma once
#pragma once
#include <vector>
#include"Algorithm.h"

using namespace std;
class Test
{
	int amount_iterations;
	int amount_state;
public:
	Test();
	int get_iterations();
	int get_state();

	void increase_iter(int numb);
	void count_states(vector<State_puzzle>& states);
};
