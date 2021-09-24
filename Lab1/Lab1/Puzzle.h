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
	int** field;	// матриця що відображає стан пазла
	int x_void;		// index row void (puzzle "0")
	int y_void;		// index column void (puzzle "0")

public:
	Puzzle();								
	Puzzle(const Puzzle& obj);				
	~Puzzle();								
	Puzzle operator=(const Puzzle& obj);
	bool operator==(const Puzzle&);
	bool operator!=(const Puzzle&);

	void random();								// функція рандомного тасування пазла
	void move(int x, int y, bool& posible);		// переміщення частини головоломки координати x i y (row i column) на пусте місце (x_void i y_void)		
												// (якщо операція успішна posible = true в іншому випадку false) 

	int get_x_void();										// отримання індекса рядка (координати x) пустоти (0)
	int get_y_void();										// отримання індекса стовпця (координати y) пустоти (0)
	int get_elem_field(int row, int column);				// отримання значення елемента пазла в координатах (row, column)
	void set_elem_field(int elem, int row, int column);		// встановлення значення (elem) елементу пазла в координатах (row, column)

	bool success();							// визначення чи головоломка в кінцевому стані  
	int calculate_heuristics();				// підрахунок еврестичної функції для поточного стану(манхетенська евристика)
	bool check_solvable();					// перевірка розв'язаності
	bool correct();

private:
	void locate_zero();					// визначення координат x_void і y_void

};


