#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#pragma once
class Puzzle
{
private:
	int** field;
	int x_void;		// index row void (puzzle "0")
	int y_void;		// index column void (puzzle "0")
	int h2;			// Manhattan heuristics
public:
	Puzzle();
	Puzzle(const Puzzle& obj);
	~Puzzle();
	Puzzle operator=(const Puzzle& obj);
	friend std::ostream& operator<<(std::ostream& out, Puzzle& obj);
	friend std::istream& operator>>(std::istream& in, Puzzle& obj);
	void write();
	void read();
	void random();
	void move(int x, int y);
	int get_h2();

private:
	void locate_zero();
	void calculate_heuristics();
};


