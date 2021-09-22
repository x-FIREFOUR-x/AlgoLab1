#include <iostream>
#include <ctime>
#include "Puzzle.h"
#include "Algorithm.h"


using namespace std;

int main()
{
    
    srand(time(NULL));

    clock_t start_time = clock();

    Puzzle l;
    l.read();
    //l.write();

    Algorithm t;
    //t.Astar(l);

    t.BFS(l);
   // t.write_solution();
    t.write_bfs_solution();

    clock_t end_time = clock() ;
    double time = (end_time - start_time) / CLOCKS_PER_SEC;
    cout << endl << "time: " << time << endl;
    return 0;
}

