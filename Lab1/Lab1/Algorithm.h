#pragma once
#include <iostream>
#include<vector>
#include<functional>
#include "Puzzle.h"

using namespace std;
struct Node				// вузел дерева(стан головоломки) потрібного алгоритму
{
	Puzzle puzzele;		// стан головоломки
	Node** ptr;			// вказівники на наступні стани
	Node* ptr_father;	// вказівник на попередній стан
	
	Node(Puzzle, Node*);
	~Node();
	
};

class Algorithm
{
	Node* row;					// вказівник на початковий стан
	vector<Puzzle> solution;	// список всіх станів (кроки від початкового до кінечного стану)
	vector<Puzzle> list_used;	// список станів у які алгоритм уже приходив
public:
	void Astar(Puzzle);			//	Алгоритм A* для розв'язання 8-puzzle
	void write_solution();		

private:
	void build_all_son(Node*);				// побудувати в дереві всі наступні стани (синів)
	int choose_sun_astar(Node* ptr_node);	// вибір наступного стану в А* за манхетенською евристикою
	void build_son(Node* ptr_node, int index, bool posible, const Puzzle& p);	// побудувати один з всіх наступних станів, якщо це можливо (чи він вже не використовувався)

	
	
};

