#include "Puzzle.h"

Puzzle::Puzzle()
{
	field = new int* [3];
	for (int i = 0; i < 3; i++)
	{
		field[i] = new int[3];
	}
}

Puzzle::Puzzle(const Puzzle& obj)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			field[i][j] = obj.field[i][j];
		}

	}
}

Puzzle::~Puzzle()
{
	for (int i = 0; i < 3; i++)
	{
		delete[]field[i];
	}
	delete[]field;

}

void Puzzle::write()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << field[i][j];
		}
	}
}

void Puzzle::read()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> field[i][j];
		}
	}
}


std::ostream& operator<<(std::ostream& out, Puzzle& obj)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			out << obj.field[i][j] << " ";
		}
		out << '\n';
	}

	return out;
}

std::istream& operator>>(std::istream& in, Puzzle& obj)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			in >> obj.field[i][j];
		}
	}

	return in;
}

/*void Puzzle::random()
{
	int* buf = new int[9];
	buf[0] = rand() % 10;
	for (int i = 1; i < 9; i++)
	{
		bool correct = false;
		while (!correct)
		{
			buf[i] = rand() % 10;
			for (int j = 0; j < i; j++)
			{
				if ()
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			field[i][j] = buf[i * 3 + j];
		}
	}
}*/