// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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

    Puzzle k ;
    k.random();
    k.write();
    k= l;

    cout << k;
}

