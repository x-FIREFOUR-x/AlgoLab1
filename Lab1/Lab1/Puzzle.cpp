#include "Puzzle.h"
Puzzle::Puzzle()
{
	field = new int* [3];
	for (int i = 0; i < 3; i++)
	{
		field[i] = new int[3];
	}

	locate_zero();
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

	return *this;
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



int Puzzle::get_x_void()
{
	return x_void;
}

int Puzzle::get_y_void()
{
	return y_void;
}

int Puzzle::get_elem_field(int row, int column)
{
	return field[row][column];
}

void Puzzle::set_elem_field(int elem, int row, int column)
{
	field[row][column] = elem;
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

int Puzzle::calculate_heuristics()
{
	int h2 = 0;
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
	return h2;
}

bool Puzzle::check_solvable()
{
	int puzzle[9];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			puzzle[i * 3 + j] = field[i][j];
		}

	}

	int inversions = 0;
	for (int i = 0; i < 9 - 1; i++) 
	{
		for (int j = i + 1; j < 9; j++) 
		{
			if (puzzle[i] && puzzle[j] && puzzle[i] > puzzle[j]) {
				inversions++;
			}
		}
	}

	if (inversions % 2 == 1) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}

bool Puzzle::correct()
{
	bool correct = true;
	vector<int> p;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			p.push_back(field[i][j]);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 9; j++)
		{
			if (p[i] == p[j])
			{
				correct = false;
			}
		}
	}

	return correct;
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

