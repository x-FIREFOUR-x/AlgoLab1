#pragma once
#include <iostream>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include <string>

#include "Puzzle.h"
#include "Test.h"
#include "State_puzzle.h"

using namespace std;
class Algorithm
{

	friend bool operator<(const pair<int, State_puzzle>&, const pair<int, State_puzzle>&);	// предикат для визначення пріоритету в пріоритетні черзі

	vector<Puzzle> list_used;		// список станів у які алгоритм уже приходив
	stack<Puzzle> solution;			// список послідовних станів від кінечного до початкогвого (у вершині початковий)
	vector<State_puzzle> states;	// список всіх станів в пам'яті
	
public:
	void Astar(Puzzle, Test& test);			//	Алгоритм A* для розв'язання 8-puzzle
	void BFS(Puzzle, Test& test);			// Алгоритм BFS для розв'язання 8-puzzle	
	stack<Puzzle> get_solution();

private:
	void search(queue<State_puzzle>& que, bool& is_search, map<string, Puzzle>& used, Test& test);										// пошук кінечного стану (BFS)
	void build_all_son(queue<State_puzzle>& que, State_puzzle current_state, int index_father, map<string, Puzzle>& used, Test& test);	// записування в чергу наступних станів від поточного (BFS)
	void build_son(queue<State_puzzle>&, Puzzle p ,int index_father, map<string, Puzzle>& used, Test& test);							// записування в чергу одного з наступних станів поточного (BFS)
	
	using prior_queue = priority_queue <pair<int, State_puzzle>, vector<pair<int, State_puzzle>>, std::greater<pair<int, State_puzzle>> >;
	void search(prior_queue &pri_queue, bool& is_search, vector<Puzzle>& used, Test& test);										// пошук кінечного стану (A*)
	void build_all_son(prior_queue &pri_queue, State_puzzle current_state, int index_father, vector<Puzzle>& used, Test& test);	// записування в чергу наступних станів від поточного (A*)
	void build_son(prior_queue &pri_queue, Puzzle p, int index_father, vector<Puzzle>& used, Test& test);							// записування в чергу одного з наступних станів поточного (A*)

	string calculate_key(Puzzle puzzle);
};
