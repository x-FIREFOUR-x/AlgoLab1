#include "Puzzle.h"

Puzzle::Puzzle()
{
	field = new int* [3];
	for (int i = 0; i < 3; i++)
	{
		field[i] = new int[3];
	}

	locate_zero();
	h2 = 0;
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
	locate_zero();
	h2 = 0;
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

	x_void = obj.x_void;
	y_void = obj.y_void;
	h2 = obj.h2;

	return *this;
}


void Puzzle::write()
{
	cout << "_____" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] != 0)
			{
				cout << field[i][j] << " ";
			}
			else
			{
				cout << "  ";
			}
			
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
			if (obj.field[i][j] != 0)
			{
				out << obj.field[i][j] << " ";
			}
			else
			{
				out <<  "  ";
			}
			
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
	//random_shuffle(buf.begin(), buf.end());
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			field[i][j] = buf[i * 3 + j];
		}
	}
}


void Puzzle::move(int x, int y, bool& possible)
{
	possible = true;
	locate_zero();
	if ((x < 3 && x >= 0 && y < 3 && y >= 0) && ((x == x_void + 1 && y == y_void) || (x == x_void && y == y_void + 1) || (x == x_void - 1 && y == y_void) || (x == x_void && y == y_void - 1)))
	{
		field[x_void][y_void] = field[x][y];
		field[x][y] = 0;
	}
	else
	{
		possible = false;
	}

}

int Puzzle::get_h2()
{
	calculate_heuristics();
	return h2;
}

int Puzzle::get_x_void()
{
	return x_void;
}

int Puzzle::get_y_void()
{
	return y_void;
}

bool Puzzle::success()
{
	bool s = true;
	for (int i = 0; i < 3; i++)	
	{
		for (int j = 0; j < 3; j++)
		{
			if (!(field[i][j] == i * 3 + j))	// перевірка чи комірка з цифрою на свому місті
			{
				s = false;
				break;
			}
		}
		if (!s)
		{
			break;
		}

	}
	return s;
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
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] != 0)
			{
				h2 += abs(field[i][j] / 3 - i) + abs(field[i][j] % 3 - j);
			}

		}
	}
}

bool Puzzle::operator==(const Puzzle& obj)
{
	bool exactly = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] != obj.field[i][j])
			{
				exactly = false;
			}
		}

	}

	return exactly;
}

 bool Puzzle::operator!=(const Puzzle& obj)
{
	bool exactly = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] != obj.field[i][j])
			{
				exactly = false;
			}
		}

	}

	return !exactly;
}

