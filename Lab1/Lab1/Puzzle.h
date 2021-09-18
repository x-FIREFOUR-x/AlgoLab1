#pragma once
#include<iostream>
using namespace std;
#pragma once
class Puzzle
{
private:
	int** field;
public:
	Puzzle();
	Puzzle(const Puzzle& obj);
	~Puzzle();
	friend std::ostream& operator<<(std::ostream& out, Puzzle& obj);
	friend std::istream& operator>>(std::istream& in, Puzzle& obj);
	void write();
	void read();
	void random();


};


