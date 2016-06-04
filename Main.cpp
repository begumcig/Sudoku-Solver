#include <iostream>
#include <fstream>
#include <sstream>
#include "Cell.h"

using namespace std;

//  Software by Elif Begum Cig. This is a simple backtracking algorithm for solving a Sudoku puzzle.  //
//  For any questions contact me at bcig@sabanciuniv.edu.  ///////////////////////////////////////////// 
//  The program reads the input from a .txt file which should be given by the user.  ///////////////////
//  Input file should consist of 9 lines and 9 colums and each number should have white space betwwen  /
//  The puzzles should be 9x9 and the empty cell inputs should be written as 0.  ///////////////////////
//  An example can be found at https://github.com/begumcig/Sudoku-Solver  //////////////////////////////
//  Feel free to contribute.  //////////////////////////////////////////////////////////////////////////                                                      


//  The function for reading the input sudoku file. //
void openFile(string fileName, ifstream & inputFile)
{
	inputFile.open(fileName.c_str());

	// checking if the input is valid. //
	while (inputFile.fail())  
	{
		cout << "Could not open the file " << fileName << endl;
		cout << "Enter the name of the input file: ";
		cin  >> fileName;
		inputFile.open(fileName.c_str());
	}		
}

//  In a sudoku every 3x3 cell has a number only once.  //////////////////////////////
//  To provide this condition, we should know the belonging 3x3 square of a cell.  //
int squareCoordinate(int xCor, int yCor)
{
	if (xCor < 3)
	{
		if (yCor < 3)
			return 1;

		else if (yCor >= 3 && yCor < 6)
			return 4;

		else if (yCor >= 6 && yCor < 9)
			return 7;
	}

	else if (xCor >= 3 && xCor < 6)
	{
		if (yCor < 3)
			return 2;

		else if (yCor >= 3 && yCor < 6)
			return 5;

		else if (yCor >= 6 && yCor < 9)
			return 8;
	}

	else if(xCor >= 6 && xCor < 9)
	{
		if (yCor < 3)
			return 3;

		else if (yCor >= 3 && yCor < 6)
			return 6;

		else if (yCor >= 6 && yCor < 9)
			return 9;
	}

	else
		cout << "Some error occured, the X and/or Y coordinates are not valid." << endl;

}

void solve(vector <Cell> & map)
{
	for(int i = 0; i< map.size(); i++)
	{

		if(map[i].changeable == true)
		{
			map[i].findPossibleValues(map);
			if(map[i].howManyPossible() > 0)
			{
				int j = 0;
				while(map[i].possibleValues[j].possible == false)
					j++;
				map[i].value = map[i].possibleValues[j].value;
				map[i].possibleValues[j].possible = false;
			}
			else
			{
				while((map[i].howManyPossible() == 0 || map[i].changeable == false) )
				{
					if(map[i].changeable == true)
						map[i].value = 0;
					i--;
				}
			
				int j = 0;
				while(map[i].possibleValues[j].possible == false)
					j++;
				map[i].value = map[i].possibleValues[j].value;
				map[i].possibleValues[j].possible = false;
			}
		}
	}
}


int main()
{
	ifstream inputFile;
	string fileName, line;
	vector <Cell> puzzleMap;
	int value;

	cout << "Please enter the name of the file: ";
	cin  >> fileName;

	openFile(fileName, inputFile);                        

	// The string stream takes the numbers form the input file and pushes them into a vector of "Cell"s.  ////////////////////////
	// Cell is the class which consists of a value and a cell coordinate element.  ///////////////////////////////////////////////
	// Value is the value of the cell and the cell coordinate is the position (x, y and the 3x3 square which the cell is in).  ///
	// Row count and column count ranges from 0 to 8 and square coordinate runs from 1 to 9.  ////////////////////////////////////

	int rowCount = 0;
	while(getline(inputFile, line))
	{
		stringstream numberStream(line);
		int columnCount = 0;
		while(numberStream >> value)
		{
			puzzleMap.push_back(Cell(value, CellCoor(columnCount, rowCount, squareCoordinate(columnCount,rowCount))));
			columnCount ++;
		}

		rowCount ++;
	}


	solve(puzzleMap); 


	for(int i= 0; i<puzzleMap.size(); i++)
	{
		cout << puzzleMap[i].value << "  " ;
		if(i%9 == 8 )
			cout << endl;

	}



	cin.get();
	cin.ignore();

	return 0;
}