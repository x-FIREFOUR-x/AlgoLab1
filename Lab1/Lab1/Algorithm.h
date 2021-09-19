#pragma once
#include <iostream>
#include<vector>
#include<functional>
#include "Puzzle.h"

using namespace std;
struct Node				// ����� ������(���� �����������) ��������� ���������
{
	Puzzle puzzele;		// ���� �����������
	Node** ptr;			// ��������� �� ������� �����
	Node* ptr_father;	// �������� �� ��������� ����
	
	Node(Puzzle, Node*);
	~Node();
	
};

class Algorithm
{
	Node* row;					// �������� �� ���������� ����
	vector<Puzzle> solution;	// ������ ��� ����� (����� �� ����������� �� �������� �����)
	vector<Puzzle> list_used;	// ������ ����� � �� �������� ��� ��������
public:
	void Astar(Puzzle);			//	�������� A* ��� ����'������ 8-puzzle
	void write_solution();		

private:
	void build_all_son(Node*);				// ���������� � ����� �� ������� ����� (����)
	int choose_sun_astar(Node* ptr_node);	// ���� ���������� ����� � �* �� ������������� ����������
	void build_son(Node* ptr_node, int index, bool posible, const Puzzle& p);	// ���������� ���� � ��� ��������� �����, ���� �� ������� (�� �� ��� �� ����������������)

	
	
};

