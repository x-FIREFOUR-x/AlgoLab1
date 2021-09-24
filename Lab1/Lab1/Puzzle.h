#pragma once
#include<iostream>
#include<cstdlib>
#include<vector>
#include <list>
#include<algorithm>

using namespace std;

class Puzzle
{
private:
	int** field;	// ������� �� �������� ���� �����
	int x_void;		// index row void (puzzle "0")
	int y_void;		// index column void (puzzle "0")

public:
	Puzzle();								
	Puzzle(const Puzzle& obj);				
	~Puzzle();								
	Puzzle operator=(const Puzzle& obj);
	bool operator==(const Puzzle&);
	bool operator!=(const Puzzle&);

	void random();								// ������� ���������� ��������� �����
	void move(int x, int y, bool& posible);		// ���������� ������� ����������� ���������� x i y (row i column) �� ����� ���� (x_void i y_void)		
												// (���� �������� ������ posible = true � ������ ������� false) 

	int get_x_void();										// ��������� ������� ����� (���������� x) ������� (0)
	int get_y_void();										// ��������� ������� ������� (���������� y) ������� (0)
	int get_elem_field(int row, int column);				// ��������� �������� �������� ����� � ����������� (row, column)
	void set_elem_field(int elem, int row, int column);		// ������������ �������� (elem) �������� ����� � ����������� (row, column)

	bool success();							// ���������� �� ����������� � �������� ����  
	int calculate_heuristics();				// ��������� ���������� ������� ��� ��������� �����(������������ ���������)
	bool check_solvable();					// �������� ����'�������
	bool correct();

private:
	void locate_zero();					// ���������� ��������� x_void � y_void

};


