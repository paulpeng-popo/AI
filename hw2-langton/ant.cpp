#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <windows.h>
using namespace std;

typedef enum Color {
    BLACK,
    WHITE,
} Color;

const int LEFT = 0;
const int UPWARD = 1;
const int RIGHT = 2;
const int DOWNWARD = 3;

class Cell{
public:
    Cell();
    int getDirection();
    void setDirection(int ratation);
    bool isNotValid();
    Color getColor();
    void change_color();
    void ant_walk();
private:
    int direction;
    Color color;
    bool ant;
};

void gotoxy(int xpos, int ypos, char str)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
    cout << str;
}

void random_init(vector<int>& list, vector<Cell>& board, int size)
{
    random_device rd;
    mt19937 generator( rd() );
    int x, y, index;
    do {
        x = rd()%size;
        y = rd()%size;
        index = (y*size+x);
    } while(board[index].isNotValid());
    list.push_back(index);
    board[index].ant_walk();
}

int theNext(int pos, int dir, int size)
{
    if(dir == UPWARD)
    {
        pos = ((pos - size) + size*size) % (size*size);
    } else if(dir == RIGHT) {
        pos = (pos + 1) % size;
    } else if(dir == DOWNWARD) {
        pos = (pos + size) % (size*size);
    } else if(dir == LEFT) {
        pos = (pos - 1) % size;
    }

    return pos;
}

void print(int pos, vector<Cell> board, int size)
{
    if(board[pos].getColor() == WHITE)
    {
        if(board[pos].isNotValid())
            gotoxy(pos/size, pos%size, 'a');
        else
            gotoxy(pos/size, pos%size, ' ');
    }
    else
    {
        if(board[pos].isNotValid())
            gotoxy(pos/size, pos%size, '@');
        else
            gotoxy(pos/size, pos%size, 'Q');
    }
}

void renew_board(vector<int> list, vector<Cell>& board, int size)
{
    int length = list.size();
    for(int i = 0; i < length; i++)
    {
        if(board[list[i]].getColor() == WHITE)
            board[list[i]].setDirection(1);
        else
            board[list[i]].setDirection(-1);
        board[list[i]].change_color();
        int temp = board[list[i]].getDirection();
        int next = theNext(list[i], temp, size);
        board[list[i]].ant_walk();
        print(list[i], board, size);
        list[i] = next;
        board[next].ant_walk();
        print(list[i], board, size);
    }
}

void show_board(vector<Cell> board, int size)
{
    system("cls");
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            int index = (i*size+j);
            if(board[index].getColor() == WHITE)
            {
                if(board[index].isNotValid())
                    cout << "a";
                else
                    cout << " ";
            }
            else
            {
                if(board[index].isNotValid())
                    cout << "@";
                else
                    cout << "Q";
            }
        }
        cout << endl;
    }
}

void Delay(int time)
{
	clock_t now = clock();
	while(clock() - now < time);
}

Cell::Cell()
{
    direction = UPWARD;
    color = WHITE;
    ant = false;
}

int Cell::getDirection()
{
    return direction;
}

void Cell::setDirection(int ratation)
{
    direction += ratation;
    direction = (direction+4) % 4;
}

bool Cell::isNotValid()
{
    return ant;
}

Color Cell::getColor()
{
    return color;
}

void Cell::change_color()
{
    if(color)
        color = BLACK;
    else
        color = WHITE;
}

void Cell::ant_walk()
{
    if(ant)
        ant = false;
    else
        ant = true;
}

int main()
{
    int size, num, timetick;
    vector <Cell> board;
    vector <int> list;

    cout << "The size of board: ";
    cin >> size;
    cout << "How many ants start with: ";
    cin >> num;
    cout << "How long will it takes: ";
    cin >> timetick;

    for(int i = 0; i < size*size; i++)
    {
        Cell square;
        board.push_back(square);
    }

    for(int i = 0; i < num; i++)
        random_init(list, board, size);

    show_board(board, size);
    while(timetick)
    {
        renew_board(list, board, size);
        Delay(500);
        timetick -= 1;
    }
    gotoxy(0, size+3, '$');
    cout << endl;
    return 0;
}
