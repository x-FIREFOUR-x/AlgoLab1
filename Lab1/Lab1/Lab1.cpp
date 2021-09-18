#include <iostream>
#include <ctime>
#include "Puzzle.h"
#include "Tree.h"


using namespace std;
int main()
{
    srand(time(NULL));
    Puzzle l;
    l.read();
    //l.write();

    Tree t;
    t.Astar(l);

    t.write_solution();
}

