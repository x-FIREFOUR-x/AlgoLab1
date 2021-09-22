#pragma once
#include <iostream>
#include<vector>
#include<stack>
#include<queue>
#include <vector>


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
	struct State_puzzle
	{
		Puzzle puzzle;
		int index_father;
		//int index_grandfather;
		//State_puzzle(Puzzle p, int ind_fa, int ind_gfa) { puzzle = p; index_father = ind_fa; index_grandfather = ind_gfa; }
		State_puzzle(Puzzle p, int ind_fa) { puzzle = p; index_father = ind_fa;}
		//const bool operator<(const State_puzzle&) { return true; }
	};
	friend bool operator<(const pair<int, Algorithm::State_puzzle>&, const pair<int, Algorithm::State_puzzle>&);

	//Node* row;					// вказівник на початковий стан
	vector<Puzzle> solution;	// список всіх станів (кроки від початкового до кінечного стану)
	vector<Puzzle> list_used;	// список станів у які алгоритм уже приходив
	stack<Puzzle> bfs_solution;
	
public:
	void Astar(Puzzle);			//	Алгоритм A* для розв'язання 8-puzzle
	void write_solution();	
	void BFS(Puzzle);			// Алгоритм BFS для розв'язання 8-puzzle
	void write_bfs_solution();

private:
	/*
	void build_all_son(Node*);				// побудувати в дереві всі наступні стани (синів)
	int choose_sun_astar(Node* ptr_node);	// вибір наступного стану в А* за манхетенською евристикою
	void build_son(Node* ptr_node, int index, bool posible, const Puzzle& p);	// побудувати один з всіх наступних станів, якщо це можливо (чи він вже не використовувався)
	*/
	void search(queue<State_puzzle>& que, bool& is_search, vector<State_puzzle>& states, vector<Puzzle>& used);			// пошук кінечного стану
	void build_all_son_bfs(queue<State_puzzle>& que, State_puzzle current_state, vector<State_puzzle>& states, int index_father, vector<Puzzle>& used);	// записування в чергу наступних станів від поточного
	void build_son_bfs(queue<State_puzzle>&, Puzzle p ,int index_father, vector<State_puzzle>& states, vector<Puzzle>& used);									// записування в чергу одного з наступних станів поточного
	
	using prior_queue = priority_queue <pair<int, State_puzzle>, vector<pair<int, State_puzzle>>, std::greater<pair<int, State_puzzle>> >;
	void search(prior_queue &pri_queue, bool& is_search, vector<State_puzzle>& states, vector<Puzzle>& used);
	void build_all_son_bfs(prior_queue &pri_queue, State_puzzle current_state, vector<State_puzzle>& states, int index_father, vector<Puzzle>& used);
	void build_son_bfs(prior_queue &pri_queue, Puzzle p, int index_father, vector<State_puzzle>& states, vector<Puzzle>& used);

};

bool operator<(const pair<int, Algorithm::State_puzzle>&, const pair<int, Algorithm::State_puzzle>&);