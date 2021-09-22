#pragma once
#include <iostream>
#include<vector>
#include<stack>
#include<queue>
#include <vector>

#include "Puzzle.h"

using namespace std;
struct Node				// ����� ������(���� �����������) ��������� ���������
{
	Puzzle puzzele;		// ���� �����������
	Node** ptr;			// ��������� �� ������� �����
	Node* ptr_father;	// �������� �� ��������� ����
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
		State_puzzle(Puzzle p, int ind_fa, int ind_gfa) { puzzle = p; index_father = ind_fa;}
	};

	Node* row;					// �������� �� ���������� ����
	vector<Puzzle> solution;	// ������ ��� ����� (����� �� ����������� �� �������� �����)
	vector<Puzzle> list_used;	// ������ ����� � �� �������� ��� ��������
	stack<Puzzle> bfs_solution;
	
public:
	void Astar(Puzzle);			//	�������� A* ��� ����'������ 8-puzzle
	void write_solution();	
	void BFS(Puzzle);			// �������� BFS ��� ����'������ 8-puzzle
	void write_bfs_solution();

private:
	void build_all_son(Node*);				// ���������� � ����� �� ������� ����� (����)
	int choose_sun_astar(Node* ptr_node);	// ���� ���������� ����� � �* �� ������������� ����������
	void build_son(Node* ptr_node, int index, bool posible, const Puzzle& p);	// ���������� ���� � ��� ��������� �����, ���� �� ������� (�� �� ��� �� ����������������)

	void search(queue<State_puzzle>& que, bool& is_search, vector<State_puzzle>& states, vector<Puzzle>& used);			// ����� �������� �����
	void build_all_son_bfs(queue<State_puzzle>& que, State_puzzle current_state, vector<State_puzzle>& states, int index_father, vector<Puzzle>& used);	// ����������� � ����� ��������� ����� �� ���������
	void build_son_bfs(queue<State_puzzle>&, Puzzle p ,int index_father, vector<State_puzzle>& states, vector<Puzzle>& used);									// ����������� � ����� ������ � ��������� ����� ���������
	
	
};

