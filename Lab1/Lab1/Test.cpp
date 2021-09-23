#include "Test.h"

Test::Test()
{
	amount_iterations = 0;
	amount_state = 0;
}

int Test::get_iterations()
{
	return amount_iterations;
}

int Test::get_state()
{
	return amount_state;
}

void Test::increase_iter(int numb)
{
	amount_iterations += numb;
}

void Test::count_states(vector<State_puzzle>& states)
{
	amount_state = states.size();
}
