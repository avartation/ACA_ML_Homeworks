#include<iostream>
#include<cstdlib>
#include<ctime>
void mazeTravel(char**, const int, int, int);
void findBegin(char**, const int, int&, int&);
void showArray(char**, const int);
bool check(const int, int, int);
void generateMaze(char**, const int);
int main()
{
	int n;
	std::cout << "Write the size of the side of the maze you want to build ";
	std::cin >> n;
	char **x = new char*[n];
	for (int i = 0; i != n; i++)
		x[i] = new char[n];
	generateMaze(x, n);
	int begin1, begin2;
	findBegin(x, n, begin1, begin2);
	showArray(x, n);
	mazeTravel(x, n, begin1, begin2);
	std::cin >> n;
}
void mazeTravel(char **x, const int size, int i, int j) // i and j are the coordinates of the begining point
{
	int s = 1;
	char d;
	x[i][j] = '.';
	if (i == 0)
		d = 6;  // right
	if (j == 0)
		d = 2;  // down
	if (i == size - 1)
		d = 4;  // left
	if (j == size - 1)
		d = 8;  // up
	while (5)
	{
		switch (d)
		{
		case 6:
			x[i][j] = '.';
			i++; x[i][j] = 'X';
			showArray(x, size);
			if (check(size, i, j))
				break;
			if (x[i][j + 1] == '.')
				d = 2;
			else if (x[i + 1][j] == '.')
				d = 6;
			else if (x[i][j - 1] == '.')
				d = 8;
			else
				d = 4;
			break;
		case 2:
			x[i][j] = '.';
			j++; x[i][j] = 'X';
			showArray(x, size);
			if (check(size, i, j))
				break;
			if (x[i - 1][j] == '.')
				d = 4;
			else if (x[i][j + 1] == '.')
				d = 2;
			else if (x[i + 1][j] == '.')
				d = 6;
			else
				d = 8;
			break;
		case 4:
			x[i][j] = '.';
			i--; x[i][j] = 'X';
			showArray(x, size);
			if (check(size, i, j))
				break;
			if (x[i][j - 1] == '.')
				d = 8;
			else if (x[i - 1][j] == '.')
				d = 4;
			else if (x[i][j + 1] == '.')
				d = 2;
			else
				d = 6;
			break;
		case 8:
			x[i][j] = '.';
			j--; x[i][j] = 'X';
			showArray(x, size);
			if (check(size, i, j))
				break;
			if (x[i + 1][j] == '.')
				d = 6;
			else if (x[i][j - 1] == '.')
				d = 8;
			else if (x[i - 1][j] == '.')
				d = 4;
			else
				d = 2;
			break;
		default:
			break;
		}
		s++;
		if (check(size, i, j))
			break;
	}
	std::cout << "\n\nNow we are out of the maze with " << s << " steps !!! Congrats bro!" << std::endl;
}
void findBegin(char **x, const int size, int& a, int& b)
{
	for (int i = 0; i != size; i++)
		if (x[i][0] == '.')
		{
			x[i][0] = 'X';
			a = i; b = 0; return;
		}
	for (int j = 0; j != size; j++)
		if (x[0][j] == '.')
		{
			x[0][j] = 'X';
			a = 0; b = j; return;
		}
	for (int i = 0; i != size; i++)
		if (x[i][size - 1] == '.')
		{
			x[i][size - 1] = 'X';
			a = i; b = size - 1; return;
		}
	for (int j = 0; j != size; j++)
		if (x[size - 1][j] == '.')
		{
			x[size - 1][j] = 'X';
			a = size - 1; b = j; return;
		}
}
void showArray(char **x, const int size)
{
	for (int i = 0; i != size; i++)
	{
		for (int j = 0; j != size; j++)
			std::cout << " " << x[i][j];
		std::cout << std::endl;
	}
	std::cout << "\n" << std::endl;
}
bool check(const int size, int i, int j)
{
	if ((i == size - 1) || (i == 0) || (j == size - 1) || (j == 0))
		return true;
	else
		return false;
}
void generateMaze(char **x, const int size)
{
	srand(time(0));
	for (int i = 0; i != size; i++)
		for (int j = 0; j != size; j++)
			x[i][j] = '#';
	int s1 = rand() % 2, s2 = rand() % 2;
	if (s1 == 0)
	{
		s1 = (s2 == 0) ? 0 : size - 1;
		s2 = rand() % (size - 2) + 1;
	}
	else
	{
		s2 = (s2 == 0) ? 0 : size - 1;
		s1 = rand() % (size - 2) + 1;
	}
	int d;
	if (s1 == 0)
		d = 0;
	else if (s1 == size - 1)
		d = 2;
	else if (s2 == 0)
		d = 1;
	else
		d = 3;
	int i;
	x[s1][s2] = '.';
	while (5)
	{
		switch (d)
		{
		case 0:
			i = rand() % (size - s1);
			std::cout << " " << 0 << " : " << i << std::endl;
			while (i != 0)
			{
				s1++;
				x[s1][s2] = '.';
				i--;
			}
			break;
		case 1:
			i = rand() % (size - s2);
			std::cout << " " << 1 << " : " << i << std::endl;
			while (i != 0)
			{
				s2++;
				x[s1][s2] = '.';
				i--;
			}
			break;
		case 2:
			i = rand() % (s1 + 1);
			std::cout << " " << 2 << " : " << i << std::endl;
			while (i != 0)
			{
				s1--;
				x[s1][s2] = '.';
				i--;
			}
			break;
		case 3:
			i = rand() % (s2 + 1);
			std::cout << " " << 3 << " : " << i << std::endl;
			while (i != 0)
			{
				s2--;
				x[s1][s2] = '.';
				i--;
			}
			break;
		default:
			break;
		}
		if (check(size, s1, s2))
			break;
		d = rand() % 4;
	}
}
