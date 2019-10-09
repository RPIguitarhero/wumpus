// 664Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stack>

using namespace std;
char board[5][5];

void move( );
void showBoard();
void initBoard();

int main()
{


}

void move()
{
	//stack 1:steps record
	//stack 2:available route record
	vector<char[5][5]> steps;
	vector<char[5][5]> options;
	int score = 0;//score, incremented by 1 from each step, by 10 for using arrow to kill wumpus

}
//initilize the game board
void initBoard()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			board[i][j] = 'O'; //O for empty slots
		}
	}
}

//display the known gameboard 
void showBoard()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << board[i][j]<<" ";
		}
		cout << "\n";
	}
}

