#include "Algorithm.h"

Node::Node(Puzzle obj)
{
	puzzele = obj;
	ptr = new Node* [4]; 
	for (int i = 0; i < 4; i++)
	{
		ptr[i] = nullptr;
	}
}

Node::~Node()
{
	for (int i = 0; i < 4; i++)
	{
		delete[]ptr[i];
	}
	delete[]ptr;
}

void Algorithm::Astar(Puzzle p)
{
	row = new Node(p);
	function<int(Node*)>specifics;
	specifics = [this] (Node* arg) { return this->choose_sun_astar(arg); };

	build_son(row, specifics);
}

void Algorithm::build_son(Node* ptr_node, function<int(Node*)> specifics)
{
	solution.push_back(ptr_node->puzzele);
	used.push_back(ptr_node->puzzele);
	//ptr_node->puzzele.write();

	if (!(ptr_node->puzzele.success()))
	{
		bool posible = true;

		Puzzle p = ptr_node->puzzele;
		p.move(ptr_node->puzzele.get_x_void() - 1, ptr_node->puzzele.get_y_void(), posible);
		if (posible)
		{
			ptr_node->ptr[0] = new Node(p);
		}

		p = ptr_node->puzzele;
		p.move(ptr_node->puzzele.get_x_void(), ptr_node->puzzele.get_y_void() - 1, posible);
		if (posible)
		{
			ptr_node->ptr[1] = new Node(p);
		}

		p = ptr_node->puzzele;
		p.move(ptr_node->puzzele.get_x_void() + 1, ptr_node->puzzele.get_y_void(), posible);
		if (posible)
		{
			ptr_node->ptr[2] = new Node(p);
		}

		p = ptr_node->puzzele;
		p.move(ptr_node->puzzele.get_x_void(), ptr_node->puzzele.get_y_void() + 1, posible);
		if (posible)
		{
			ptr_node->ptr[3] = new Node(p);
		}

		
		/*bool is_swap = false;
		for (int i = 0; i < used.size(); i++)
		{
			if (ptr_node->ptr[number_son]->puzzele == used[i])
			{
				for (int i = 0; i < 4; i++)
				{
					if (i != number_son && ptr_node->ptr[i] != nullptr && !(ptr_node->ptr[i]->puzzele == ptr_node->puzzele))
					{
						number_son = i;
						is_swap = true;
						break;
					}
				}
				if (is_swap)
				{
					break;
				}
			}
		}*/


		int number_son = specifics(ptr_node);					// вибір сина згідно специфіки алгоритму (визначається в переданій алгоритмом функції в обгортку specifics)
		
		build_son(ptr_node->ptr[number_son], specifics);		// рекурсивний виклик для побудови нащадків вибраного сина
	}

}

int Algorithm::choose_sun_astar(Node* ptr_node)
{
	int number_son;
	int min_h2 = 1000;
	int p_h2;
	for (int i = 0; i < 4; i++)
	{
		if (ptr_node->ptr[i] != nullptr)
		{
			ptr_node->ptr[i]->puzzele.calculate_heuristics();
			p_h2 = ptr_node->ptr[i]->puzzele.get_h2();

			if (p_h2 < min_h2)
			{
				min_h2 = p_h2;
				number_son = i;
			}
		}
	}
	return number_son;
}

void Algorithm::write_solution()
{

	cout << "======STEPS========" << endl;
	for (int i = 0; i < solution.size(); i++)
	{
		cout << solution[i];
	}
}


