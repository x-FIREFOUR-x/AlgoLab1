#pragma once
#include<iostream>

#include<cstdlib>
#include<vector>
#include<algorithm>

using namespace std;

class Puzzle
{
private:
	int** field;	// матриця що відображає стан пазла
	int x_void;		// index row void (puzzle "0")
	int y_void;		// index column void (puzzle "0")
	//int h2 = 0;			// Manhattan heuristics

public:
	Puzzle();								
	Puzzle(const Puzzle& obj);				
	~Puzzle();								
	Puzzle operator=(const Puzzle& obj);	

	friend std::ostream& operator<<(std::ostream& out, Puzzle& obj);
	friend std::istream& operator>>(std::istream& in, Puzzle& obj);
	void write();
	void read();

	void random();								// функція рандомного тасування пазла
	void move(int x, int y, bool& posible);		// переміщення частини головоломки координати x i y (row i column) на пусте місце (x_void i y_void)		
												// (якщо операція успішна posible = true в іншому випадку false) 

	//int get_h2();
	int get_x_void();
	int get_y_void();

	bool success();								// визначення чи головоломка в кінцевому стані  
	int calculate_heuristics();				// підрахунок еврестичної функції для поточного стану(манхетенська евристика)

	bool operator==(const Puzzle&);
	bool operator!=(const Puzzle&);

private:
	void locate_zero();					// визначення координат x_void і y_void

};


