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
	row = new Node(p, nullptr);		// створення початкового стану в корні дерева
	build_all_son(row);				// вхід в рекурсивну функцію побудови всіх синів вибраного предка
}

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



void Algorithm::write_solution()
{

	cout << "======STEPS===" << solution.size() - 1 <<  "=====" << endl;
	for (int i = 0; i < solution.size(); i++)
	{
		cout << solution[i];
	}
}

void Algorithm::BFS(Puzzle p)
{
	bool is_search = false;
	Node* ptr = nullptr;
	if (!p.success())
	{
		row = new Node(p, nullptr);		// створення початкового стану в корні дерева
		while (!is_search)
		{
			 ptr = search(row, is_search);
		}
		
	}
	else
	{	
		bfs_solution.push(p);
		p.write();
	}
	if (ptr != nullptr)
	{
		bfs_solution.push(ptr->puzzele);
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

Node* Algorithm::search(Node* ptr_node,bool& is_search)
{
	
		for (int i = 0; i < 4; i++)
		{
			if (is_search)
			{
				bfs_solution.push(ptr_node->puzzele);
				ptr_node->puzzele.write();
				return ptr_node->ptr_father;
			}
			else
			{
				if (ptr_node->ptr[i] != nullptr)
				{
					search(ptr_node->ptr[i], is_search);
				}
				else
				{
					if (ptr_node->is_son != true)
					{
						build_all_son_bfs(ptr_node, is_search);
						break;
					}
						
				}
			}
			
		}
	


	return nullptr;
}

void Algorithm::build_all_son_bfs(Node* ptr_node, bool& is_search)
{
	bool posible;
	int k = 0;

	Puzzle p = ptr_node->puzzele;
	p.move(ptr_node->puzzele.get_x_void() - 1, ptr_node->puzzele.get_y_void(), posible);
	build_son_bfs(ptr_node, posible, k, p);

	p = ptr_node->puzzele;
	p.move(ptr_node->puzzele.get_x_void() + 1, ptr_node->puzzele.get_y_void(), posible);
	build_son_bfs(ptr_node, posible, k, p);

	p = ptr_node->puzzele;
	p.move(ptr_node->puzzele.get_x_void(), ptr_node->puzzele.get_y_void() - 1, posible);
	build_son_bfs(ptr_node, posible, k, p);

	p = ptr_node->puzzele;
	p.move(ptr_node->puzzele.get_x_void(), ptr_node->puzzele.get_y_void() + 1, posible);
	build_son_bfs(ptr_node, posible, k, p);


	//cout << "********************" << endl;
	//ptr_node->puzzele.write();

	for (int i = 0; i < 4; i++)
	{
		if (ptr_node->ptr[i] != nullptr)
		{
			//ptr_node->ptr[i]->puzzele.write();
			if (ptr_node->ptr[i]->puzzele.success()){
				bfs_solution.push(ptr_node->ptr[i]->puzzele);
				is_search = true;
			}
		}
			
	}
	//cout << "++++++++++++++++++++++" << endl;
	ptr_node->is_son = true;
}

void Algorithm::build_son_bfs(Node* ptr_node, bool posible, int& k, Puzzle p)
{
	if (posible) {
		if (ptr_node->ptr_father != nullptr)
		{
			if (ptr_node->ptr_father->puzzele != p)
			{
				ptr_node->ptr[k] = new Node(p, ptr_node);
				k++;
			}
		}
		else
		{
			ptr_node->ptr[k] = new Node(p, ptr_node);
			k++;
		}

	}
}

