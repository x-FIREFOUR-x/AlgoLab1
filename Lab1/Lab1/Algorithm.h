#pragma once
#include <iostream>
#include<vector>
#include<stack>
#include<functional>
#include "Puzzle.h"

using namespace std;
struct Node				// вузел дерева(стан головоломки) потрібного алгоритму
{
	Puzzle puzzele;		// стан головоломки
	Node** ptr;			// вказівники на наступні стани
	Node* ptr_father;	// вказівник на попередній стан
	bool is_son;
	
	Node(Puzzle, Node*);
	~Node();
	
};

class Algorithm
{
	Node* row;					// вказівник на початковий стан
	vector<Puzzle> solution;	// список всіх станів (кроки від початкового до кінечного стану)
	vector<Puzzle> list_used;	// список станів у які алгоритм уже приходив
	stack<Puzzle> bfs_solution;
	
public:
	void Astar(Puzzle);			//	Алгоритм A* для розв'язання 8-puzzle
	void write_solution();	
	void BFS(Puzzle);
	void write_bfs_solution();

private:
	void build_all_son(Node*);				// побудувати в дереві всі наступні стани (синів)
	int choose_sun_astar(Node* ptr_node);	// вибір наступного стану в А* за манхетенською евристикою
	void build_son(Node* ptr_node, int index, bool posible, const Puzzle& p);	// побудувати один з всіх наступних станів, якщо це можливо (чи він вже не використовувався)

	Node* search(Node* row, bool&);
	void build_all_son_bfs(Node* row, bool&);
	
	
};

