#include "conway.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <windows.h>

Cell::Cell()
{
	alive = false;
}

bool Cell::getstatus()
{
	return alive;
}

void Cell::change()
{
	if(alive)
		alive = false;
	else
		alive = true;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;   
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void Delay(int time)
{
	clock_t now = clock();
	while(clock() - now < time);
}

void Print(vector< vector<Cell> > area)
{
	for(int i = 0; i < area.size(); i++)
	{
		for(int j = 0; j < area[i].size(); j++)
		{
			if(area[i][j].getstatus())
				cout << "@ ";
			else
				cout << "  ";
		}
		cout << endl;
	}
}

Pos* Random(Pos dots[], int size, int N)
{
	srand(time(NULL));
	dots = new Pos[size];
	for(int i = 0; i < size; i++)
	{
		dots[i].x = rand() % N;
		dots[i].y = rand() % N;
		for(int j = 0; j < i; j++)
		{
			if(dots[j].x == dots[i].x && dots[j].y == dots[i].y)
			{
				i -= 1;
				break;
			}
		}
	}
	
	return dots;
}

void Initial(Pos dots[], int size, vector< vector<Cell> >& area)
{
	
	for(int q = 0; q < size; q++)
	{
		int i = dots[q].x;
		int j = dots[q].y;
		area[i][j].change();
	}
}

void DeadOrAlive(const int size, const int i, const int j, vector<Pos>& Move, vector< vector<Cell> > area)
{
	Pos mark = {i, j};
	int alive_around = 0;
	
	for(int p = 0; p < 8; p++)
	{
		int x = i + nine_bias[p].x;
		int y = j + nine_bias[p].y;
		
		if(x < 0 || y < 0 || x >= size || y >= size) continue;
		
		if((area[x][y]).getstatus())
			alive_around += 1;
	}
	
	if(area[i][j].getstatus())
	{
		if(alive_around < 2 || alive_around > 3)
			Move.push_back(mark);
	}
	else
	{
		if(alive_around == 3)
			Move.push_back(mark);
	}
}

void Run(const int size, vector< vector<Cell> >& area)
{
	vector<Pos> Move;
	for(int i = 0; i < area.size(); i++)
	{
		for(int j = 0; j < area[i].size(); j++)
		{
			DeadOrAlive(size, i, j, Move, area);
		}
	}
	
	for(int s = 0; s < Move.size(); s++)
	{
		int a = Move[s].x;
		int b = Move[s].y;
		area[a][b].change();
		gotoxy(b*2, a);
		if(area[a][b].getstatus())
			cout << "@ ";
		else
			cout << "  ";
	}
}

void Reset_board(int size, vector< vector<Cell> >& area)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(area[i][j].getstatus())
				area[i][j].change();
		}
	}
}

void Display(string str)
{
	for(int i = 0; i < str.length(); i++)
	{
		cout << str[i];
		Delay(10);
	}
	cout << endl;
}


