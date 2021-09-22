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

	void search(queue<pair<int,Puzzle>>& que, bool& is_search, vector<pair<int, Puzzle>>& states);			// ����� �������� �����
	void build_all_son_bfs(queue<pair<int, Puzzle>>& que, pair<int, Puzzle> current_state, vector<pair<int, Puzzle>>& states, int index_father);	// ����������� � ����� ��������� ����� �� ���������
	void build_son_bfs(queue<pair<int, Puzzle>>&, Puzzle p ,int index_father);									// ����������� � ����� ������ � ��������� ����� ���������
	
	
};

