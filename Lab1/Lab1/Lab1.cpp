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

    Algorithm t;

    int k;
    cout << "choose:" << endl;
    cin >> k;

    unsigned int start = clock();
    if (k == 1)
    {
        t.BFS(l);
        t.write_solution();
    }
    else
    {
        if (k == 2)
        {
            t.Astar(l);
            t.write_solution();
        }
    }

    unsigned int end = clock();
    cout << (float)(end - start)/1000 << endl;
    

   

    return 0;
}

