#include "Interface.h"

void Interface::consol_intface()
{
    cout << "Input start state:" << endl;
    Puzzle puzzle = read_puzzle();
    
    Algorithm algo;
    Test test;

    int choose;
    cout << "choose algorithm (1 - BFS, 2 - A*):";
    cin >> choose;

    unsigned int start = clock();
    if (choose == 1)
    {
        cout << "---BFS---" << endl;
        algo.BFS(puzzle, test);
        write_solution(algo);
    }
    else
    {
        if (choose == 2)
        {
            cout << "---A*---" << endl;
            algo.Astar(puzzle, test);
            write_solution(algo);
        }
    }

    write_test_stats(test);

    unsigned int end = clock();
    cout << "time: " <<(float)(end - start) / 1000 << endl;
}

Puzzle Interface::read_puzzle()
{
    Puzzle puzzle;
    int elem;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> elem;
            puzzle.set_elem_field(elem, i, j);
        }

    }
    return puzzle;
}

void Interface::write_puzzle(Puzzle puzzle)
{
    int elem;
    cout << "_____" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            elem = puzzle.get_elem_field(i, j);
            if (elem == 0){
                cout << "  ";
            }
            else{
                cout << elem << " ";
            }
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

void Interface::write_solution(Algorithm& algo)
{
    stack<Puzzle> solution = algo.get_solution();
    cout << "======STEPS===" << solution.size() - 1 << "=====" << endl;
    Puzzle p;
    while (!solution.empty())
    {
        write_puzzle(solution.top());
        solution.pop();
    }
}

void Interface::write_test_stats(Test test)
{
    cout << endl << "___Test___" << endl;
    cout << "iterations: " << test.get_iterations() << endl;
    cout << "states in memory(all states): " << test.get_state() << endl;
}
