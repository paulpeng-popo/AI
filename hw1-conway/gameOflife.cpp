#include "conway.h"
#include <iostream>
#include <fstream>
#include <csignal>
#include <string>
#include <conio.h>
#define N 50

int SIG = 0;
void signalHandler(int signum)
{
	SIG = signum;
}

int main()
{
	Cell cell;
	vector<Cell> row;
	row.assign(N,cell);
	vector< vector<Cell> > Board;
	Board.assign(N,row);
	
	char filename[] = "patterns.txt";
	string title = "Name: Conway's Game of Life Model";
	string text1 = "Step: 1.Give an initial pattern\n";
	string text2 = "      2.Process seeds by some rules\n";
	string text3 = "      3.Repeat\n";
	string text4 = "      4.Get a series of cell-pictures\n";
	string subtitle = "#Program implemented by B073040002";
	
	int empty;
	system("cls");
	Display(title);
	Display(text1+text2+text3+text4);
	Display(subtitle);
	cout << endl;
	
	cout << "Press 'right' key to continue!!!";
	Delay(700);
	for(int i = 0; i < 3; i++)
	{
		cout << "\b";
		cout << " ";
		cout << "\b";
		Delay(300);
	}
	
	string end = "...";
	for(int i = 0; i < 3; i++)
	{
		cout << end[i];
		Delay(300);
	}
	empty = getch();
	empty = getch();
	
	Pos* dots;
	string token;
	int size_dots;
	int temp_x, temp_y;
	ifstream pfile;
	
	RESELECT:	
	pfile.open(filename);
	pfile.seekg(0, ios::beg);
	while(true)
	{
		size_dots = 0;
		system("cls");
		cout << "Select the initial pattern" << endl;
		cout << endl;
		
		pfile >> token;
		Display(token);
		pfile >> size_dots;
		if(size_dots)
		{
			dots = new Pos[size_dots];
			for(int i = 0; i < size_dots; i++)
			{
				pfile >> temp_x;
				pfile >> temp_y;
				dots[i].x = temp_x;
				dots[i].y = temp_y;
			}
		}
		else
		{
			size_dots = N*N*11/20;
			dots = Random(dots, size_dots, N);
		}
		
		empty = getch();
		empty = getch();
		
		if(empty == 13)
			break;
		else
		{
			if(empty == 'q') exit(1);
			if(token == "Random_pattern")
				pfile.seekg(0, ios::beg);
		}
	}
	pfile.close();
	
	system("cls");
	Initial(dots, size_dots, Board);
	Print(Board);
	
	SIG = 0;
	signal(SIGINT, signalHandler);
	while(true)
	{
		Delay(100);
		Run(N, Board);
		if(SIG) break;
	}
	
	if(SIG)
	{
		delete dots;
		Reset_board(N, Board);
		goto RESELECT;
	}
	
	return 0;
}


