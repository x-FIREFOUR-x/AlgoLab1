#include "Algorithm.h"

bool operator<(const pair<int, Algorithm::State_puzzle>& lhs, const pair<int, Algorithm::State_puzzle>& rhs)
{
	return lhs.first < rhs.first;
}

void Algorithm::Astar(Puzzle start_puzzle)
{
	prior_queue pri_queue;

	int h2 = start_puzzle.calculate_heuristics();
	State_puzzle st_puzzle(start_puzzle, -1);

	pri_queue.push(pair(h2, st_puzzle));

	vector<State_puzzle> states;
	vector<Puzzle> used;

	bool is_search = false;
	while (!is_search)
	{
		search(pri_queue, is_search, states, used);
	}

	int current_index = (states.size() - 1);
	State_puzzle current_puzzle = states[current_index];
	while (current_puzzle.puzzle != start_puzzle)
	{
		solution.push(current_puzzle.puzzle);
		current_index = current_puzzle.index_father;
		current_puzzle = states[current_index];
	}
	solution.push(current_puzzle.puzzle);
}

void Algorithm::search(prior_queue &pri_queue, bool& is_search, vector<State_puzzle>& states, vector<Puzzle>& used)
{
	State_puzzle current_state = pri_queue.top().second;
	pri_queue.pop();

	states.push_back(current_state);
	used.push_back(current_state.puzzle);

	if (!current_state.puzzle.success())
	{
		build_all_son(pri_queue, current_state, states, states.size() - 1, used);
	}
	else
	{
		is_search = true;
	}

}

void Algorithm::build_all_son(prior_queue &pri_queue, State_puzzle current_state, vector<State_puzzle>& states, int index_father, vector<Puzzle>& used)
{
	Puzzle new_puz = current_state.puzzle;
	bool posible;

	new_puz.move(new_puz.get_x_void() - 1, new_puz.get_y_void(), posible);
	build_son(pri_queue, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void() + 1, new_puz.get_y_void(), posible);
	build_son(pri_queue, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() - 1, posible);
	build_son(pri_queue, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() + 1, posible);
	build_son(pri_queue, new_puz, index_father, states, used);
}

void Algorithm::build_son(prior_queue &pri_queue, Puzzle new_puz, int index_father, vector<State_puzzle>& states, vector<Puzzle>& used)
{
	bool is_copy = false;
	for (int i = 0; i < used.size(); i++)
	{
		if (used[i] == new_puz)
		{
			is_copy = true;
			break;
		}
	}

	if (!is_copy)
	{
		int h2 = new_puz.calculate_heuristics();
		State_puzzle st_puzzle(new_puz, index_father);

		pri_queue.push(pair(h2, st_puzzle));
	}
}

void Algorithm::BFS(Puzzle start_puzzle)
{
	queue<State_puzzle> que;
	que.push(State_puzzle(start_puzzle, -1));

	vector<State_puzzle> states;
	vector<Puzzle> used;

	bool is_search = false;
	while (!is_search)
	{
		search(que, is_search, states, used);
	}
	
	int current_index = (states.size() - 1);
	State_puzzle current_puzle = states[current_index];
	while (current_puzle.puzzle != start_puzzle)
	{
		solution.push(current_puzle.puzzle);
		current_index = current_puzle.index_father;
		current_puzle = states[current_index];
	}
	solution.push(current_puzle.puzzle);
}

void Algorithm::search(queue<State_puzzle>& que, bool& is_search, vector<State_puzzle>& states, vector<Puzzle>& used)
{
	State_puzzle current_state = que.front();
	que.pop();

	states.push_back(current_state);
	used.push_back(current_state.puzzle);
	
	if (!current_state.puzzle.success())
	{
		build_all_son(que, current_state, states, states.size()-1, used);
	}
	else
	{
		is_search = true;
	}
	
}

void Algorithm::build_all_son(queue<State_puzzle>& que, State_puzzle current_state, vector<State_puzzle>& states, int index_father, vector<Puzzle>& used)
{
	Puzzle new_puz = current_state.puzzle;
	bool posible;

	new_puz.move(new_puz.get_x_void() - 1, new_puz.get_y_void(), posible);
	build_son(que, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void() + 1, new_puz.get_y_void(), posible);
	build_son(que, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() - 1, posible);
	build_son(que, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() + 1, posible);
	build_son(que, new_puz, index_father, states, used);
}

void Algorithm::build_son(queue<State_puzzle>& que, Puzzle new_puz, int index_father, vector<State_puzzle>& states, vector<Puzzle>& used)
{
	int index_prafather = states[index_father].index_father;

	bool is_copy = false;
	for (int i = 0; i < used.size(); i++)
	{
		if (used[i] == new_puz)
		{
			is_copy = true;
			break;
		}
	}

	if(!is_copy)
	{
		que.push(State_puzzle(new_puz, index_father));
	}
}


/*void Algorithm::write_solution()
{
	cout << "======STEPS===" << solution.size()-1 << "=====" << endl;
	Puzzle p;
	while(!solution.empty())
	{ 
		cout << solution.top();
		solution.pop();
	}
}*/

stack<Puzzle> Algorithm::get_solution()
{
	return solution;
}

