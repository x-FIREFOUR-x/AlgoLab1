#pragma once
#include <iostream>
#include<vector>
#include<stack>
#include<queue>
#include <vector>

#include "Puzzle.h"

using namespace std;

class Algorithm
{
	struct State_puzzle			// ���� �����
	{
		Puzzle puzzle;		// �������� ����
		int index_father;	// ������ ������������ ����� � ������ 
		State_puzzle(Puzzle p, int ind_fa) 
		{ 
			puzzle = p; 
			index_father = ind_fa;
		}
	};

	friend bool operator<(const pair<int, Algorithm::State_puzzle>&, const pair<int, Algorithm::State_puzzle>&);	// �������� ��� ���������� ��������� � ��������� ����

	vector<Puzzle> list_used;		// ������ ����� � �� �������� ��� ��������
	stack<Puzzle> solution;			// ������ ���������� ����� �� �������� �� ������������ (� ������ ����������)
	vector<State_puzzle> states;	// ������ ��� ����� � ���'��
	
public:
	void Astar(Puzzle);			//	�������� A* ��� ����'������ 8-puzzle
	void BFS(Puzzle);			// �������� BFS ��� ����'������ 8-puzzle	
	stack<Puzzle> get_solution();

private:
	void search(queue<State_puzzle>& que, bool& is_search, vector<Puzzle>& used);										// ����� �������� ����� (BFS)
	void build_all_son(queue<State_puzzle>& que, State_puzzle current_state, int index_father, vector<Puzzle>& used);	// ����������� � ����� ��������� ����� �� ��������� (BFS)
	void build_son(queue<State_puzzle>&, Puzzle p ,int index_father, vector<Puzzle>& used);							// ����������� � ����� ������ � ��������� ����� ��������� (BFS)
	
	using prior_queue = priority_queue <pair<int, State_puzzle>, vector<pair<int, State_puzzle>>, std::greater<pair<int, State_puzzle>> >;
	void search(prior_queue &pri_queue, bool& is_search, vector<Puzzle>& used);										// ����� �������� ����� (A*)
	void build_all_son(prior_queue &pri_queue, State_puzzle current_state, int index_father, vector<Puzzle>& used);	// ����������� � ����� ��������� ����� �� ��������� (A*)
	void build_son(prior_queue &pri_queue, Puzzle p, int index_father, vector<Puzzle>& used);							// ����������� � ����� ������ � ��������� ����� ��������� (A*)

};
