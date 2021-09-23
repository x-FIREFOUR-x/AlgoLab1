#include "Algorithm.h"

bool operator<(const pair<int, State_puzzle>& lhs, const pair<int, State_puzzle>& rhs)
{
	return lhs.first < rhs.first;
}

void Algorithm::Astar(Puzzle start_puzzle)
{
	prior_queue pri_queue;

	int h2 = start_puzzle.calculate_heuristics();
	State_puzzle st_puzzle(start_puzzle, -1);

	pri_queue.push(pair(h2, st_puzzle));

	vector<Puzzle> used;

	bool is_search = false;
	while (!is_search)
	{
		search(pri_queue, is_search, used);
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

void Algorithm::search(prior_queue &pri_queue, bool& is_search, vector<Puzzle>& used)
{
	State_puzzle current_state = pri_queue.top().second;
	pri_queue.pop();

	states.push_back(current_state);
	used.push_back(current_state.puzzle);

	if (!current_state.puzzle.success())
	{
		build_all_son(pri_queue, current_state, states.size() - 1, used);
	}
	else
	{
		is_search = true;
	}

}

void Algorithm::build_all_son(prior_queue &pri_queue, State_puzzle current_state, int index_father, vector<Puzzle>& used)
{
	Puzzle new_puz = current_state.puzzle;
	bool posible;

	new_puz.move(new_puz.get_x_void() - 1, new_puz.get_y_void(), posible);
	build_son(pri_queue, new_puz, index_father, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void() + 1, new_puz.get_y_void(), posible);
	build_son(pri_queue, new_puz, index_father, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() - 1, posible);
	build_son(pri_queue, new_puz, index_father, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() + 1, posible);
	build_son(pri_queue, new_puz, index_father, used);
}

void Algorithm::build_son(prior_queue &pri_queue, Puzzle new_puz, int index_father, vector<Puzzle>& used)
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

string Algorithm::calculate_key(Puzzle puzzle)
{
	string key = "";
	string k;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			k = to_string(puzzle.get_elem_field(i, j));
			key = key + k;
		}
	}
	return key;
}

void Algorithm::BFS(Puzzle start_puzzle)
{
	queue<State_puzzle> que;
	que.push(State_puzzle(start_puzzle, -1));

	map<string, Puzzle> used;

	bool is_search = false;
	while (!is_search)
	{
		search(que, is_search, used);
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

void Algorithm::search(queue<State_puzzle>& que, bool& is_search, map<string, Puzzle>& used)
{
	State_puzzle current_state = que.front();
	que.pop();
	//cout << que.size() << endl;

	states.push_back(current_state);

	string key = calculate_key(current_state.puzzle);
	used[key] = current_state.puzzle;

	if (!current_state.puzzle.success())
	{
		build_all_son(que, current_state, states.size()-1, used);
	}
	else
	{
		is_search = true;
	}
	
}

void Algorithm::build_all_son(queue<State_puzzle>& que, State_puzzle current_state, int index_father, map<string, Puzzle>& used)
{
	Puzzle new_puz = current_state.puzzle;
	bool posible;

	new_puz.move(new_puz.get_x_void() - 1, new_puz.get_y_void(), posible);
	build_son(que, new_puz, index_father, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void() + 1, new_puz.get_y_void(), posible);
	build_son(que, new_puz, index_father, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() - 1, posible);
	build_son(que, new_puz, index_father, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() + 1, posible);
	build_son(que, new_puz, index_father, used);
}

void Algorithm::build_son(queue<State_puzzle>& que, Puzzle new_puz, int index_father, map<string, Puzzle>& used)
{
	string key = calculate_key(new_puz);
	map<string,Puzzle>::iterator it = used.find(key);
	
	if(it == used.end())
	{
		que.push(State_puzzle(new_puz, index_father));
	}
}


stack<Puzzle> Algorithm::get_solution()
{
	return solution;
}