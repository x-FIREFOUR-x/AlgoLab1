#pragma once
#include<iostream>

#include<cstdlib>
#include<vector>
#include<algorithm>

using namespace std;

class Puzzle
{
private:
	int** field;
	int x_void;		// index row void (puzzle "0")
	int y_void;		// index column void (puzzle "0")
	int h2 = 0;			// Manhattan heuristics
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
	void move(int x, int y, bool& posible);
	int get_h2();
	int get_x_void();
	int get_y_void();
	bool success();
	void calculate_heuristics();
	bool operator==(const Puzzle&);

private:
	void locate_zero();

};


