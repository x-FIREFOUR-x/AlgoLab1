#pragma once
#include <iostream>
#include<vector>
#include "Puzzle.h"

using namespace std;
struct Node
{
	Puzzle puzzele;
	Node** ptr;
	
	Node(Puzzle);
	~Node();
	
};

class Tree
{
	Node* row;
	vector<Puzzle> solution;
	vector<Puzzle> used;
public:
	void Astar(Puzzle);
	void build_son(Node*);

	void write_solution();
	
};

