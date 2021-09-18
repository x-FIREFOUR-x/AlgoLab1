#include <iostream>
#include <ctime>
#include "Puzzle.h"

using namespace std;
int main()
{
    srand(time(NULL));
    Puzzle l;
    l.read();
    l.write();

    cout << endl << l.get_h2() << endl;
}

