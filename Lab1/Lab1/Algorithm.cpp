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
	row = new Node(p, nullptr);		// ��������� ����������� ����� � ���� ������
	build_all_son(row);				// ���� � ���������� ������� �������� ��� ���� ��������� ������
}

void Algorithm::build_all_son(Node* ptr_node)
{
	solution.push_back(ptr_node->puzzele);			// ��������� ��������� ����� � ����'����
	list_used.push_back(ptr_node->puzzele);			// ��������� ��������� ����� � ������ ������������ �����
	//ptr_node->puzzele.write();

	if (!(ptr_node->puzzele.success()))		// �������� �� �� �� ������� � ������� ����
	{
		bool posible = true;

						// �������� � ����� ��� ��������� ����� ��������, � �������� �� ��� ���� ������� � ��������
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

			if (p_h2 < min_h2)		// �������� �� �� � ����� ����� ����� ������-����� ��� � ���������
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
	if (posible)			// ����� �� ������� �� ���������� �������� move (�� ����� ������ ���������� ������ �� ����� ����������)
	{
		if (ptr_node->ptr_father != nullptr)	// �� � ��������� ����
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
			if ( ptr_node->ptr_father->puzzele !=  p && !is_copy)	// �������� �� ��������� ���� �� ������� � �����-��������� � �� �� ��� �� ��������
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
	if (!p.success())
	{
		row = new Node(p, nullptr);		// ��������� ����������� ����� � ���� ������
		search(row, is_search);
	}
	else
	{	
		bfs_solution.push(p);
	}

}

Node* Algorithm::search(Node* ptr_node,bool& is_search)
{
	while (!is_search)
	{
		for (int i = 0; i < 4; i++)
		{
			if (ptr_node->ptr[i] != nullptr)
			{
				search(ptr_node->ptr[i], is_search);
			}
			else
			{
				build_all_son_bfs(ptr_node);
			}
		}
	}


	return nullptr;
}

void Algorithm::build_all_son_bfs(Node* ptr_node)
{
	bool posible;
	int k = 0;

	Puzzle p = ptr_node->puzzele;
	p.move(ptr_node->puzzele.get_x_void() - 1, ptr_node->puzzele.get_y_void(), posible);
	if (posible) {
		ptr_node->ptr[k] = new Node(p, ptr_node);
		k++;
	}

	p = ptr_node->puzzele;
	p.move(ptr_node->puzzele.get_x_void() + 1, ptr_node->puzzele.get_y_void(), posible);
	if (posible)
	{
		ptr_node->ptr[k] = new Node(p, ptr_node);
		k++;
	}

	p = ptr_node->puzzele;
	p.move(ptr_node->puzzele.get_x_void(), ptr_node->puzzele.get_y_void() - 1, posible);
	if (posible)
	{
		ptr_node->ptr[k] = new Node(p, ptr_node);
		k++;
	}

	p = ptr_node->puzzele;
	p.move(ptr_node->puzzele.get_x_void(), ptr_node->puzzele.get_y_void() + 1, posible);
	if (posible)
	{
		ptr_node->ptr[k] = new Node(p, ptr_node);
	}
}

