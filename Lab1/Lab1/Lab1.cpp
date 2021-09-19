#include <iostream>
#include <functional>
#include <ctime>
#include "Puzzle.h"
#include "Algorithm.h"


using namespace std;

int main()
{
    srand(time(NULL));
    Puzzle l;
    l.read();
    //l.write();

    Algorithm t;
    t.Astar(l);

    t.write_solution();
    
    return 0;
}

