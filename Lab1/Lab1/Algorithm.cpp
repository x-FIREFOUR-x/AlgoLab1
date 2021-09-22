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

void Algorithm::Astar(Puzzle p)
{
	row = new Node(p, nullptr);		// ��������� ����������� ����� � ����� ������
	build_all_son(row);				// ���� � ���������� ������� �������� ��� ����� ��������� ������
}

void Algorithm::build_all_son(Node* ptr_node)
{
	solution.push_back(ptr_node->puzzele);			// ��������� ��������� ����� � ����'����
	list_used.push_back(ptr_node->puzzele);			// ��������� ��������� ����� � ������ ������������ ������
	//ptr_node->puzzele.write();

	if (!(ptr_node->puzzele.success()))		// �������� �� �� �� ������� � ������� ����
	{
		bool posible = true;

						// �������� � ����� ��� ��������� ������ ��������, � �������� �� ��� ���� ������� � ��������
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

		int number_son = choose_sun_astar(ptr_node);	// ���� ���� ����� ������������ ���������
		
		build_all_son(ptr_node->ptr[number_son]);		// ����������� ������ ��� �������� ��� ������� ��������� ����
	}

}

int Algorithm::choose_sun_astar(Node* ptr_node)
{
	int number_son ;		// ����� ��������� ���� (� ��������� min_h2)
	int min_h2 = 1000;		// �������� �������� ����������-���
	int p_h2;				// �������� ����������-���

	for (int i = 0; i < 4; i++)					
	{
		if (ptr_node->ptr[i] != nullptr)
		{
			ptr_node->ptr[i]->puzzele.calculate_heuristics();		// ������ ����������-������� ��� �����
			p_h2 = ptr_node->ptr[i]->puzzele.get_h2();

			if (p_h2 < min_h2)		// �������� �� �� � ����� ����� ����� ������-����� ��� � ����������
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
	if (posible)			// ����� �� ������� �� ����������� �������� move (�� ����� ������ ���������� ������ �� ����� ����������)
	{
		if (ptr_node->ptr_father != nullptr)	// �� � ���������� ����
		{
			bool is_copy = false;		
			for (int i = 0; i <list_used.size() ; i++)	// �������� �� ��� ���� ��� �� ��� ������������
			{
				if (list_used[i] == p)
				{
					is_copy = true;
					break;
				}
			}
			if ( ptr_node->ptr_father->puzzele !=  p && !is_copy)	// �������� �� ��������� ���� �� ������� � �����-���������� � �� �� ��� �� ��������
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




void Algorithm::write_solution()
{

	cout << "======STEPS===" << solution.size() - 1 <<  "=====" << endl;
	for (int i = 0; i < solution.size(); i++)
	{
		cout << solution[i];
	}
}

void Algorithm::BFS(Puzzle statrt_puzzle)
{
	queue<State_puzzle> que;
	que.push(State_puzzle(statrt_puzzle, -1, -1));
	vector<State_puzzle> states;

	bool is_search = false;
	while (!is_search)
	{
		search(que, is_search, states);
	}
	
	int current_index = (states.size() - 1);
	State_puzzle current_puzle = states[current_index];
	while (current_puzle.puzzle != statrt_puzzle)
	{
		bfs_solution.push(current_puzle.puzzle);
		current_index = current_puzle.index_father;
		current_puzle = states[current_index];
	}
	bfs_solution.push(current_puzle.puzzle);
}

void Algorithm::search(queue<State_puzzle>& que, bool& is_search, vector<State_puzzle>& states)
{
	State_puzzle current_state = que.front();
	que.pop();
	states.push_back(current_state);
	
	if (!current_state.puzzle.success())
	{
		build_all_son_bfs(que, current_state, states, states.size()-1);
	}
	else
	{
		is_search = true;
	}
	
}

void Algorithm::build_all_son_bfs(queue<State_puzzle>& que, State_puzzle current_state, vector<State_puzzle>& states, int index_father)
{
	Puzzle new_puz = current_state.puzzle;
	bool posible;

	new_puz.move(new_puz.get_x_void() - 1, new_puz.get_y_void(), posible);
	build_son_bfs(que, new_puz, index_father, states);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void() + 1, new_puz.get_y_void(), posible);
	build_son_bfs(que, new_puz, index_father, states);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() - 1, posible);
	build_son_bfs(que, new_puz, index_father, states);

	new_puz = current_state.puzzle;
	new_puz.move(new_puz.get_x_void(), new_puz.get_y_void() + 1, posible);
	build_son_bfs(que, new_puz, index_father, states);
}

void Algorithm::build_son_bfs(queue<State_puzzle>& que, Puzzle new_puz, int index_father, vector<State_puzzle>& states)
{
	int index_prafather = states[index_father].index_father;
	if (index_prafather != -1)
	{
		if (states[index_prafather].puzzle != new_puz)
		{
			que.push(State_puzzle(new_puz, index_father, index_prafather));
		}
	}
	else
	{
		que.push(State_puzzle(new_puz, index_father, states[index_father].index_father));
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

