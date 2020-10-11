#ifndef __CONWAY_H__
#define __CONWAY_H__

#include <vector>
#include <string>
using namespace std;

typedef struct Position{
	int x;
	int y;
}Pos;

const Pos nine_bias[8] = {-1, -1, 
						  -1,  0, 
						  -1,  1, 
						   0, -1, 
						   0,  1, 
						   1, -1, 
						   1,  0, 
						   1,  1};

class Cell{
	public:
		Cell();
		bool getstatus();
		void change();
	private:
		bool alive;
};

void gotoxy(int xpos, int ypos);
void Delay(int time);
void Print(vector< vector<Cell> > area);
Pos* Random(Pos dots[], int size, int N);
void Initial(Pos dots[], int size, vector< vector<Cell> >& area);
void DeadOrAlive(const int size, const int i, const int j, vector<Pos>& Move, vector< vector<Cell> > area);
void Run(const int size, vector< vector<Cell> >& area);
void Reset_board(int size, vector< vector<Cell> >& area);
void Display(string str);

#endif
