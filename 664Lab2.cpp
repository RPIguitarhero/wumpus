// 664Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author:Kai Kang

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

//using a oversized board. This means the game cannot be bigger than 10 by 10
//I'm just too lazy to use a real variable size 2d array in Boost libray.
string gameboard[10][10], //gameboard for tester to set up the scenario
AIboard[10][10];//AIboard for AI to run its algorithm
void move();
void showBoard(int width, int height);
void initBoard(int width, int height);

int main()
{
	cout << "what's the size of the gameboard? input 55 for a 5 by 5 gameboard.\n";
	string input;
	getline(cin, input);
	int width = int(input[0])-48, //NO input check, assumed user input is in correct format
		height = int(input[1]) - 48;
	initBoard(width,height);
	showBoard(width, height);//DEBUG
}

void move()
{
	//stack 1:steps record
	//stack 2:available route record
	
	int score = 0;//score, incremented by 1 from each step, by 10 for using arrow to kill wumpus
}

//ask the player to initilize the game board
void initBoard(int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			gameboard[i][j] = 'U'; //U for currently unknown slots
			AIboard[i][j] = 'U';
		}
	}

	//"USER MANUAL"
	cout << "Please keep entering the description for the board. For example, input 00E for starting location at topleft corner\n";
	cout << " 33GB for the 4th row 4th column slot to have gold and breeze. \n";
	cout << "input END(case sensitive) when you're done with the description. \n";

	string input;
	do
	{
		getline(cin, input);
		gameboard[int(input[0]) - 48][int(input[1]) - 48] = input.substr( 2, 2); //copy the 3rd and 4th(if there is a 4th) char onto the board
	} while (input!="END");
}

//display the known gameboard 
void showBoard(int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << gameboard[i][j] << " ";
		}
		cout << "\n";
	}
}
