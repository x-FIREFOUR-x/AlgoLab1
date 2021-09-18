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
	int x_void;
	int y_void;
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

private:
	void locate_zero();
};


