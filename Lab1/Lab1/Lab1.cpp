#include <iostream>
#include <ctime>
#include "Puzzle.h"

using namespace std;
int main()
{
    srand(time(NULL));
    Puzzle l;
    l.random();
    l.write();

    int x, y;
    cin >> x >> y;
    l.move(x, y);
    l.write();
}

