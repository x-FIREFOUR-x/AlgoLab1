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
	field = new int* [3];
	for (int i = 0; i < 3; i++)
	{
		field[i] = new int[3];
	}

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

Puzzle Puzzle::operator=(const Puzzle& obj)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			field[i][j] = obj.field[i][j];
		}
	}

	return *this;
}


void Puzzle::write()
{
	cout << "_____" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << field[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-----" << endl;
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
	out << "_____" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			out << obj.field[i][j] << " ";
		}
		out << '\n';
	}
	out << "-----" << endl;

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

void Puzzle::random()
{
	vector<int> buf;
	for (int i = 0; i < 9; i++)
	{
		buf.push_back(i);
	}
	random_shuffle(buf.begin(), buf.end());
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			field[i][j] = buf[i * 3 + j];
		}
	}
}
