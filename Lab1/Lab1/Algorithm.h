#pragma once
#include <iostream>
#include<vector>
#include<functional>
#include "Puzzle.h"

using namespace std;
struct Node
{
	Puzzle puzzele;
	Node** ptr;
	
	Node(Puzzle);
	~Node();
	
};

class Algorithm
{
	Node* row;
	vector<Puzzle> solution;
	vector<Puzzle> used;
public:
	void Astar(Puzzle);
	void write_solution();

private:
	void build_son(Node*, function<int(Node*)> specifics);
	int choose_sun_astar(Node* ptr_node);

	
	
};

