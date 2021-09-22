#include "Algorithm.h"

Node::Node(Puzzle obj, Node* p_father)
{
	puzzele = obj;
	ptr = new Node* [4]; 
	for (int i = 0; i < 4; i++)
	{
		ptr[i] = nullptr;
	}

	ptr_father = p_father;
	is_son = false;
}

Node::~Node()
{
	for (int i = 0; i < 4; i++)
	{
		delete[]ptr[i];
	}
	delete[]ptr;

	delete ptr_father;
}


void Algorithm::Astar(Puzzle start_puzzle)
{
	priority_queue <pair<int, State_puzzle>, vector<pair<int, State_puzzle>>, greater<pair<int, State_puzzle>>> pri_queue;

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
		bfs_solution.push(current_puzzle.puzzle);
		current_index = current_puzzle.index_father;
		current_puzzle = states[current_index];
	}
	bfs_solution.push(current_puzzle.puzzle);
}

void Algorithm::search(priority_queue<pair<int, State_puzzle>, vector<pair<int, State_puzzle>>, greater<pair<int, State_puzzle>>> &pri_queue, bool& is_search, vector<State_puzzle>& states, vector<Puzzle>& used)
{
	State_puzzle current_state = pri_queue.top().second;
	pri_queue.pop();

	states.push_back(current_state);
	used.push_back(current_state.puzzle);

	if (!current_state.puzzle.success())
	{
		build_all_son_bfs(pri_queue, current_state, states, states.size() - 1, used);
	}
	else
	{
		is_search = true;
	}

}

void Algorithm::build_all_son_bfs(priority_queue<pair<int, State_puzzle>, vector<pair<int, State_puzzle>>, greater<pair<int, State_puzzle>>> &pri_queue, State_puzzle current_state, vector<State_puzzle>& states, int index_father, vector<Puzzle>& used)
{
	Puzzle new_puz = current_state.puzzle;
	bool posible;

	new_puz.move(new_puz.get_x_void() - 1, new_puz.get_y_void(), posible);
	build_son_bfs(pri_queue, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void() + 1, new_puz.get_y_void(), posible);
	build_son_bfs(pri_queue, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() - 1, posible);
	build_son_bfs(pri_queue, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() + 1, posible);
	build_son_bfs(pri_queue, new_puz, index_father, states, used);
}

void Algorithm::build_son_bfs(priority_queue<pair<int, State_puzzle>, vector<pair<int, State_puzzle>>, greater<pair<int, State_puzzle>>> &pri_queue, Puzzle new_puz, int index_father, vector<State_puzzle>& states, vector<Puzzle>& used)
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

/*
void Algorithm::build_all_son(Node* ptr_node)
{
	solution.push_back(ptr_node->puzzele);			// додавання поточного стану в розв'язок
	list_used.push_back(ptr_node->puzzele);			// додавання поточного стану в список використаних станів
	//ptr_node->puzzele.write();

	if (!(ptr_node->puzzele.success()))		// перевірка чи ми не прийшли в кінечний стан
	{
		bool posible = true;

						// побудова в дереві всіх наступних станів роздільно, і перевірка чи цей стан потрібен і можливий
		Puzzle p = ptr_node->puzzele;	
		p.move(ptr_node->puzzele.get_x_void() - 1, ptr_node->puzzele.get_y_void(), posible);
		build_son(ptr_node, 0, posible, p);

		p = ptr_node->puzzele;
		p.move(ptr_node->puzzele.get_x_void(), ptr_node->puzzele.get_y_void() - 1, posible);
		build_son(ptr_node, 1, posible, p);

		p = ptr_node->puzzele;
		p.move(ptr_node->puzzele.get_x_void() + 1, ptr_node->puzzele.get_y_void(), posible);
		build_son(ptr_node, 2, posible, p);

		p = ptr_node->puzzele;
		p.move(ptr_node->puzzele.get_x_void(), ptr_node->puzzele.get_y_void() + 1, posible);
		build_son(ptr_node, 3, posible, p);

		int number_son = choose_sun_astar(ptr_node);	// вибір сина згідно манхетенської евристики
		
		build_all_son(ptr_node->ptr[number_son]);		// рекурсивний виклик для побудови всіх нащадків вибраного сина
	}

}

int Algorithm::choose_sun_astar(Node* ptr_node)
{
	int number_son ;		// номер вибраного сина (з найменшим min_h2)
	int min_h2 = 1000;		// найменше значення евристичної-фун
	int p_h2;				// значення евристичної-фун

	for (int i = 0; i < 4; i++)					
	{
		if (ptr_node->ptr[i] != nullptr)
		{
			ptr_node->ptr[i]->puzzele.calculate_heuristics();		// виклик евристичної-функції для стану
			p_h2 = ptr_node->ptr[i]->puzzele.get_h2();

			if (p_h2 < min_h2)		// перевірка чи ци в цього стану менша еврист-функц чим в попередніх
			{
				min_h2 = p_h2;
				number_son = i;
			}
		}
	}

	return number_son;
}

void Algorithm::build_son(Node* ptr_node, int index, bool posible, const Puzzle& p)
{
	if (posible)			// змінна що відповідає за коректність операції move (чи можна взагалі перемістити комірку на пусту координату)
	{
		if (ptr_node->ptr_father != nullptr)	// чи є попередній стан
		{
			bool is_copy = false;		
			for (int i = 0; i <list_used.size() ; i++)	// перевірка чи цей стан уже не був використаний
			{
				if (list_used[i] == p)
				{
					is_copy = true;
					break;
				}
			}
			if ( ptr_node->ptr_father->puzzele !=  p && !is_copy)	// перевірка чи наступний стан не співпадає з перед-попереднім і чи він вже не використ
			{
				ptr_node->ptr[index] = new Node(p, ptr_node);
			}
		}
		else
		{
			ptr_node->ptr[index] = new Node(p, ptr_node);
		}
		
		//if (index == 3 && ptr_node->ptr[0] == nullptr && ptr_node->ptr[0] == nullptr &&)
	}
}
*/



void Algorithm::write_solution()
{

	cout << "======STEPS===" << solution.size() - 1 <<  "=====" << endl;
	for (int i = 0; i < solution.size(); i++)
	{
		cout << solution[i];
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
		bfs_solution.push(current_puzle.puzzle);
		current_index = current_puzle.index_father;
		current_puzle = states[current_index];
	}
	bfs_solution.push(current_puzle.puzzle);
}

void Algorithm::search(queue<State_puzzle>& que, bool& is_search, vector<State_puzzle>& states, vector<Puzzle>& used)
{
	State_puzzle current_state = que.front();
	que.pop();

	states.push_back(current_state);
	used.push_back(current_state.puzzle);
	
	if (!current_state.puzzle.success())
	{
		build_all_son_bfs(que, current_state, states, states.size()-1, used);
	}
	else
	{
		is_search = true;
	}
	
}

void Algorithm::build_all_son_bfs(queue<State_puzzle>& que, State_puzzle current_state, vector<State_puzzle>& states, int index_father, vector<Puzzle>& used)
{
	Puzzle new_puz = current_state.puzzle;
	bool posible;

	new_puz.move(new_puz.get_x_void() - 1, new_puz.get_y_void(), posible);
	build_son_bfs(que, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void() + 1, new_puz.get_y_void(), posible);
	build_son_bfs(que, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() - 1, posible);
	build_son_bfs(que, new_puz, index_father, states, used);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() + 1, posible);
	build_son_bfs(que, new_puz, index_father, states, used);
}

void Algorithm::build_son_bfs(queue<State_puzzle>& que, Puzzle new_puz, int index_father, vector<State_puzzle>& states, vector<Puzzle>& used)
{
	int index_prafather = states[index_father].index_father;

	/*if (index_prafather != -1)
	{
		if (states[index_prafather].puzzle != new_puz)
		{
			que.push(State_puzzle(new_puz, index_father, index_prafather));
		}
	}
	else
	{
		que.push(State_puzzle(new_puz, index_father, states[index_father].index_father));
	}*/

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


void Algorithm::write_bfs_solution()
{
	cout << "======STEPS===" << bfs_solution.size()-1 << "=====" << endl;
	Puzzle p;
	while(!bfs_solution.empty())
	{ 
		cout << bfs_solution.top();
		bfs_solution.pop();
	}
}

