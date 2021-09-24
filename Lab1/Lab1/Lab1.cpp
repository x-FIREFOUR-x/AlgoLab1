#include <iostream>
#include <ctime>
#include "Interface.h"
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    Interface console;
    console.consol_intface();

    return 0;
}

