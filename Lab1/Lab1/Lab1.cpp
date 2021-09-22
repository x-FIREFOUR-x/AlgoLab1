#include <iostream>
#include <ctime>
#include <chrono>
#include <queue>
#include "Puzzle.h"
#include "Algorithm.h"
#include <time.h>


using namespace std;

int main()
{
    
    srand(time(NULL));

    Puzzle l;
    l.read();
    unsigned int start = clock();
    //l.write();

    Algorithm t;
    t.Astar(l);

    //t.BFS(l);
   // t.write_solution();
    t.write_bfs_solution();

    unsigned int end = clock();
    cout << (float)(end - start)/1000 << endl;
    

   

    return 0;
}

