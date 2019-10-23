// CS664 Artificial Intelligence Lab2
// Author:Kai Kang

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

//using a oversized board. Note that the game cannot be bigger than 10 by 10.
//I'm just too lazy to use a dynamic 2D array or a real variable-size 2d array in Boost libray.
string gameboard[10][10], //gameboard for tester to set up the scenario
	AIboard[10][10];//AIboard for AI to run its algorithm, all slots unkonwn except for the starting location
vector<vector<int>> route,//(1000, vector<int>(2, 0)),//a stack to track the correct route, size of 500 pairs of path at start
options;// (1000, vector<int>(2, 0)); //a stack to track available adjacent slots, size of 1000 at start
int points = 0; //accumulating points 

vector<int> move(int height, int width, vector<int> currentLocation);
void showBoard(int width, int height, bool isGameboard);
void initBoard(int width, int height);
vector<int> setStart(int width, int height);


int main()
{
	cout << "what's the size of the gameboard? input 44 for a 5 by 5 gameboard.\n";
	string input;
	getline(cin, input);
	int width = int(input[0]) - 48, //NO input check, assumed user input is in correct format
		height = int(input[1]) - 48;
	initBoard(width, height);
	showBoard(width, height, 1);//DEBUG
	vector<int> startLocation = setStart(height, width),
		currentLocation;
	//cout << startLocation[0]<<" "<<startLocation[1];//DEBUG
	currentLocation = startLocation;

	do //keep moving until gold is found
	{
		currentLocation = move(height, width, currentLocation);
		showBoard(width, height, 0); //DEBUG 
	} while (gameboard[currentLocation[0]][currentLocation[1]].find("G") == string::npos);
}

//CORE:algorithm per step, should return the currentLocation after this step
vector<int> move(int height, int width, vector<int> currentLocation)
{
	int i = currentLocation[0],
		j = currentLocation[1];
	//read the current slot and store possible nearby information
	AIboard[i][j] = gameboard[i][j];//AI now knows everything about this slot

	if (AIboard[i][j].find('B') != string::npos)//"Breezy"
	{
		if (i + 1 <= height)//check boundary for down slot
		{
			if (AIboard[i + 1][j].find("p") != string::npos) //definitely a pit, mark with 'P' 
			{
				AIboard[i + 1][j] = "P";
			}
			if (AIboard[i + 1][j] == "U") //potentially a pit, mark with 'p'
			{
				AIboard[i + 1][j]="p";
			}
			if (AIboard[i + 1][j] == "w") //potentially a pit, add mark 'p'
			{
				AIboard[i + 1][j] += "p";
			}
		}

		if (j + 1 <= width)//check boundary for right slot
		{
			if (AIboard[i][j+1].find("p") != string::npos) //definitely a pit, mark with 'P' 
			{
				AIboard[i][j + 1] = "P";
			}
			if (AIboard[i][j + 1] == "U") //potentially a pit, mark with 'p'
			{
				AIboard[i][j + 1] = "p";
			}
			if (AIboard[i][j + 1] == "w") //potentially a pit, add mark 'p'
			{
				AIboard[i][j + 1] += "p";
			}
		}

		if (i - 1 >=0)//check boundary for up slot
		{
			if (AIboard[i-1][j ].find("p") != string::npos) //definitely a pit, mark with 'P' 
			{
				AIboard[i-1][j ] = "P";
			}
			if (AIboard[i-1][j ] == "U") //potentially a pit, mark with 'p'
			{
				AIboard[i-1][j ] = "p";
			}
			if (AIboard[i-1][j ] == "w") //potentially a pit, add mark 'p'
			{
				AIboard[i-1][j ] += "p";
			}
		}

		if (j - 1 >=0)//check boundary for left slot
		{
			if (AIboard[i][j - 1].find("p") != string::npos) //definitely a pit, mark with 'P' 
			{
				AIboard[i][j - 1] = "P";
			}
			if (AIboard[i][j - 1] == "U") //potentially a pit, mark with 'p'
			{
				AIboard[i][j - 1] = "p";
			}
			if (AIboard[i][j - 1] == "w") //potentially a pit, add mark 'p'
			{
				AIboard[i][j - 1] += "p";
			}
		}
	}

	if (AIboard[i][j].find('S') != string::npos)//"stench", mark adjacent slots as potential wumpus 'w'
	{
		if (i + 1 <= height)//check boundary for down slot
		{
			if (AIboard[i + 1][j].find("w") != string::npos) //definitely a wumpus
			{
				AIboard[i + 1][j] = "W";
			}
			if (AIboard[i + 1][j] == "U") //potentially a wumpus, mark with 'w'
			{
				AIboard[i + 1][j] = "w";
			}
			if (AIboard[i + 1][j] == "p") //potentially a wumpus, add mark 'p'
			{
				AIboard[i + 1][j] += "w";
			}
		}

		if (j + 1 <= width)//check boundary for right slot
		{
			if (AIboard[i][j + 1].find("w") != string::npos) //definitely a wumpus
			{
				AIboard[i][j + 1] = "W";
			}
			if (AIboard[i][j + 1] == "U") //potentially a wumpus, mark with 'w'
			{
				AIboard[i][j + 1] = "w";
			}
			if (AIboard[i][j + 1] == "p") //potentially a wumpus, add mark 'p'
			{
				AIboard[i][j + 1] += "w";
			}
		}

		if (i-1 >= 0)//check boundary for up slot
		{
			if (AIboard[i - 1][j].find("w") != string::npos) //definitely a wumpus
			{
				AIboard[i - 1][j] = "W";
			}
			if (AIboard[i - 1][j] == "U") //potentially a wumpus, mark with 'w'
			{
				AIboard[i - 1][j] = "w";
			}
			if (AIboard[i - 1][j] == "p") //potentially a wumpus, add mark 'p'
			{
				AIboard[i - 1][j] += "w";
			}
		}

		if (j - 1 >=0)//check boundary for left slot
		{
			if (AIboard[i][j - 1].find("w") != string::npos) //definitely a wumpus
			{
				AIboard[i][j - 1] = "W";
			}
			if (AIboard[i][j - 1] == "U") //potentially a wumpus, mark with 'w'
			{
				AIboard[i][j - 1] = "w";
			}
			if (AIboard[i][j - 1] == "p") //potentially a wumpus, add mark 'p'
			{
				AIboard[i][j - 1] += "w";
			}
		}
	}

	if (AIboard[i][j].find("G") != string::npos)//"Gold" current location has gold
	{
		if (AIboard[i][j].find("W") != string::npos)//wumpus is with gold
		{
			points += 10;//10 points for using arrow to kill the wumpus
		}
		return vector<int> {i,j};
	}

	if (AIboard[i][j] == "U" || AIboard[i][j]=="E") //empty or starting slot, nothing in particular
	{
		AIboard[i][j] = " "; //this slot is now explored, mark with space
		if (i+1 <= height)//check boundary for down slot
		{
			if (AIboard[i + 1][j].find("p") != string::npos || AIboard[i + 1][j].find("w") != string::npos)//definitely not a Pit nor wumpus, mark with "F"
			{
				AIboard[i + 1][j] = "F";
				options.push_back(vector<int>{i + 1, j}); //record on the options stack
			}
			else if (AIboard[i + 1][j] == "U") 
			{ 
				AIboard[i + 1][j] = "F"; 
				options.push_back(vector<int>{i + 1, j});
			}
		}

		if (j+1 <= width)//check boundary for right slot
		{
			if (AIboard[i][j+1].find("p") != string::npos || AIboard[i][j + 1].find("w") != string::npos)
			{
				AIboard[i][j+1] = "F";
				options.push_back(vector<int>{i , j+1});
			}
			else if (AIboard[i][j + 1] == "U") 
			{ 
				AIboard[i][j + 1] = "F"; 
				options.push_back(vector<int>{i, j + 1});
			}
		}


		if (i-1 >=0)//check boundary for up slot
		{
			if (AIboard[i-1][j].find("p") != string::npos || AIboard[i - 1][j].find("w") != string::npos)
			{
				AIboard[i-1][j] = "F";
				options.push_back(vector<int>{i-1, j});
			}
			else if (AIboard[i - 1][j] == "U")
			{
				AIboard[i - 1][j] = "F";
				options.push_back(vector<int>{i - 1, j});
			}
		}

		if (j-1>=0)//check boundary for left slot
		{
			if (AIboard[i][j - 1].find("p") != string::npos || AIboard[i][j - 1].find("w") != string::npos)
			{
				AIboard[i][j - 1] = "F";
				options.push_back(vector<int>{i, j-1 });
			}
			else if(AIboard[i][j - 1] == "U") 
			{ 
				AIboard[i][j - 1] = "F"; 
				options.push_back(vector<int>{i, j - 1 });
			}
		}
	}

	//record the path to route
	route.push_back(currentLocation);
	route.push_back(options.back());


	//move to the most recent option
	return options.back();
}

//CORE check if an adjacent slot is a potential choice
bool isAvailable(vector<int> slot)
{

	return true;

}


//CORE:ask the player to initilize the game board
void initBoard(int width, int height)
{
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			gameboard[i][j] = "U"; //U for currently unknown slots
			AIboard[i][j] = "U";
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
		gameboard[int(input[0]) - 48][int(input[1]) - 48] = input.substr(2, 2); //copy the 3rd and 4th(if there is a 4th) char onto the board
	} while (input != "END");
}

//HELPER: display the AI or game board
void showBoard(int width, int height, bool isGameBoard)
{
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (isGameBoard == 1)
			{
				cout << gameboard[i][j] << " ";
			}
			else { cout << AIboard[i][j] << " "; }
		}
		cout << "\n";
	}
}

//CORE:set up the starting location
vector<int> setStart(int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (gameboard[i][j].find('E') != string::npos)
			{
				return vector<int>{i, j};
				cout << "starting location found, starting\n";
			}
		}
		cout << "starting location not found, please check your input\n";
	}
}

