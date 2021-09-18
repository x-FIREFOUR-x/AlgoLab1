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


void Puzzle::move(int x, int y)
{
	locate_zero();
	if ( (x<3 && x>=0 && y<3 && y>=0 ) && ((x==x_void+1 && y==y_void) || (x==x_void && y==y_void+1) || (x==x_void-1 && y==y_void) || (x==x_void && y==y_void-1)) )
	{
		field[x_void][y_void] = field[x][y];
		field[x][y] = 0;
	}
	else
	{
		cout << "!! Eror move can't !!" << endl;
	}
	
}

int Puzzle::get_h2()
{
	calculate_heuristics();
	return h2;
}

void Puzzle::locate_zero()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] == 0)
			{
				x_void = i;
				y_void = j;
			}
		}

	}
}

void Puzzle::calculate_heuristics()
{
	h2 = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] != 0)
			{
				cout << abs(field[i][j] / 3 - i) + abs(field[i][j] % 3 - j) << endl;
				h2 += abs(field[i][j] / 3 - i) + abs(field[i][j] % 3 - j);
			}
			
		}
	}
}
